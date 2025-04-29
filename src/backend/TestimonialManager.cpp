#include "TestimonialManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QDebug>

// singleton instance getter
TestimonialManager& TestimonialManager::getInstance() {
    static TestimonialManager instance;
    return instance;
}

// constructor
TestimonialManager::TestimonialManager() : m_trackingTimer(new QTimer(this)) {
    // fetch testimonials from webservice
    connect(&client, &ApiClient::GoodGetReply,    this, &TestimonialManager::onGoodGetResponse);
    connect(&client, &ApiClient::BadGetReply,     this, &TestimonialManager::onBadGetResponse);
    connect(&client, &ApiClient::GoodPostReply,   this, &TestimonialManager::onGoodPostResponse);
    connect(&client, &ApiClient::BadPostReply,    this, &TestimonialManager::onBadPostResponse);
    client.GetTestimonials();

    // check every minute if we should show prompt
    connect(m_trackingTimer, &QTimer::timeout, this, &TestimonialManager::checkTimeAndPrompt);
    m_trackingTimer->setInterval(60000);
}

// destructor
TestimonialManager::~TestimonialManager() {
    saveTestimonials();
}

// file-based loading is deprecated
void TestimonialManager::loadTestimonials() {
    // no-op: replaced by GET from webservice
}

// save by sending to webservice instead of file
void TestimonialManager::saveTestimonials() {
    std::string jsonOut = Parser::TestimonialsToJson(m_testimonials);
    client.PostTestimonials(jsonOut);
}

// add new testimonial then save
void TestimonialManager::addTestimonial(const Testimonial& testimonial) {
    m_testimonials.append(testimonial);
    saveTestimonials();
}

// return only satisfactory testimonials
QVector<Testimonial> TestimonialManager::getSatisfactoryTestimonials() const {
    QVector<Testimonial> satisfactory;
    for (const Testimonial& t : m_testimonials) {
        if (t.isSatisfactory()) {
            satisfactory.append(t);
        }
    }
    return satisfactory;
}

// check if a user already gave a testimonial
bool TestimonialManager::hasUserGivenTestimonial(const QString& username) const {
    for (const Testimonial& t : m_testimonials) {
        if (t.getAuthor() == username) {
            return true;
        }
    }
    return false;
}

// set “do not show again” preference
void TestimonialManager::setDoNotShowAgain(const QString& username, bool value) {
    m_doNotShowAgain[username] = value;
    saveTestimonials();
}

// get “do not show again” preference
bool TestimonialManager::getDoNotShowAgain(const QString& username) const {
    return m_doNotShowAgain.value(username, false);
}

// start/stop time tracking
void TestimonialManager::startTrackingTime() {
    m_trackingTimer->start();
}
void TestimonialManager::stopTrackingTime() {
    m_trackingTimer->stop();
}

// every minute, decide if testimonial prompt should fire
void TestimonialManager::checkTimeAndPrompt() {
    QString currentUser; // TODO: retrieve from UserManager
    if (hasUserGivenTestimonial(currentUser) || getDoNotShowAgain(currentUser)) {
        return;
    }
    int& userTime = m_userTimeTracking[currentUser];
    userTime += 1;  // add one minute
    if (userTime == INITIAL_PROMPT_TIME ||
        (userTime > INITIAL_PROMPT_TIME && (userTime - INITIAL_PROMPT_TIME) % REPEAT_PROMPT_TIME == 0)) {
        emit shouldPromptForTestimonial();
    }
}

// slot: GET /testimonials succeeded
void TestimonialManager::onGoodGetResponse(const QString& json) {
    m_testimonials = parse.JsonToTestimonials(json.toStdString());
}

// slot: GET /testimonials failed
void TestimonialManager::onBadGetResponse(const QString& error) {
    qDebug() << "Error fetching testimonials:" << error;
}

// slot: POST /testimonials succeeded
void TestimonialManager::onGoodPostResponse() {
    qDebug() << "Testimonials saved to server.";
}

// slot: POST /testimonials failed
void TestimonialManager::onBadPostResponse(const QString& error) {
    qDebug() << "Error saving testimonials:" << error;
}