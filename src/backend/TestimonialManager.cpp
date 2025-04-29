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

// setup timer and load existing testimonials
TestimonialManager::TestimonialManager() : m_trackingTimer(new QTimer(this)) {
    // ensure database directory exists
    QDir().mkpath("database");
    
    loadTestimonials();
    
    // check every minute if we should show prompt
    connect(m_trackingTimer, &QTimer::timeout, this, &TestimonialManager::checkTimeAndPrompt);
    m_trackingTimer->setInterval(60000);
    qDebug() << "Current path:" << QDir::currentPath();
}

// save testimonials when manager is destroyed
TestimonialManager::~TestimonialManager() {
    saveTestimonials();
}

// load testimonials from json file
void TestimonialManager::loadTestimonials() {
    QFile file("database/testimonials.json");
    
    // create file if it doesn't exist
    if (!file.exists()) {
        saveTestimonials();  // creates empty file
        return;
    }
    
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open testimonials file for reading:" << file.errorString();
        return;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    // handle empty file
    if (data.isEmpty()) {
        return;
    }
    
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Failed to parse testimonials file:" << parseError.errorString();
        return;
    }
    
    if (!doc.isArray()) {
        qDebug() << "Testimonials file is not a JSON array";
        return;
    }
    
    QJsonArray array = doc.array();
    m_testimonials.clear();
    
    for (const QJsonValue& value : array) {
        if (!value.isObject()) {
            qDebug() << "Invalid testimonial entry - not an object";
            continue;
        }
        m_testimonials.append(Testimonial::fromJson(value.toObject()));
    }
    
    // also load do not show preferences
    QFile prefsFile("database/testimonial_preferences.json");
    if (prefsFile.open(QIODevice::ReadOnly)) {
        QJsonDocument prefsDoc = QJsonDocument::fromJson(prefsFile.readAll());
        if (prefsDoc.isObject()) {
            QJsonObject prefs = prefsDoc.object();
            for (auto it = prefs.begin(); it != prefs.end(); ++it) {
                m_doNotShowAgain[it.key()] = it.value().toBool();
            }
        }
        prefsFile.close();
    }
}

// save testimonials to json file
void TestimonialManager::saveTestimonials() {
    // save testimonials
    QFile file("database/testimonials.json");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open testimonials file for writing:" << file.errorString();
        return;
    }
    
    QJsonArray array;
    for (const Testimonial& testimonial : m_testimonials) {
        array.append(testimonial.toJson());
    }
    
    QJsonDocument doc(array);
    if (file.write(doc.toJson()) == -1) {
        qDebug() << "Failed to write testimonials:" << file.errorString();
    }
    file.close();
    
    // save do not show preferences
    QFile prefsFile("database/testimonial_preferences.json");
    if (prefsFile.open(QIODevice::WriteOnly)) {
        QJsonObject prefs;
        for (auto it = m_doNotShowAgain.begin(); it != m_doNotShowAgain.end(); ++it) {
            prefs[it.key()] = it.value();
        }
        QJsonDocument prefsDoc(prefs);
        prefsFile.write(prefsDoc.toJson());
        prefsFile.close();
    }
}

// add new testimonial and save to file
void TestimonialManager::addTestimonial(const Testimonial& testimonial) {
    m_testimonials.append(testimonial);
    saveTestimonials();  // save immediately after adding
}

// get list of testimonials marked as satisfactory
QVector<Testimonial> TestimonialManager::getSatisfactoryTestimonials() const {
    QVector<Testimonial> satisfactory;
    for (const Testimonial& testimonial : m_testimonials) {
        if (testimonial.isSatisfactory()) {
            satisfactory.append(testimonial);
        }
    }
    return satisfactory;
}

// check if user has already given a testimonial
bool TestimonialManager::hasUserGivenTestimonial(const QString& username) const {
    for (const Testimonial& testimonial : m_testimonials) {
        if (testimonial.getAuthor() == username) {
            return true;
        }
    }
    return false;
}

// set do not show again preference for user
void TestimonialManager::setDoNotShowAgain(const QString& username, bool value) {
    m_doNotShowAgain[username] = value;
    saveTestimonials();  // save preferences immediately
}

// get do not show again preference for user
bool TestimonialManager::getDoNotShowAgain(const QString& username) const {
    return m_doNotShowAgain.value(username, false);
}

// start tracking user time
void TestimonialManager::startTrackingTime() {
    m_trackingTimer->start();
}

// stop tracking user time
void TestimonialManager::stopTrackingTime() {
    m_trackingTimer->stop();
}

// check if we should show testimonial prompt
void TestimonialManager::checkTimeAndPrompt() {
    QString currentUser = ""; // get from user manager
    if (hasUserGivenTestimonial(currentUser) || getDoNotShowAgain(currentUser)) {
        return;
    }
    
    int& userTime = m_userTimeTracking[currentUser];
    userTime += 1; // add one minute
    
    // show prompt at 30 min and every hour after if declined
    if (userTime == INITIAL_PROMPT_TIME || 
        (userTime > INITIAL_PROMPT_TIME && (userTime - INITIAL_PROMPT_TIME) % REPEAT_PROMPT_TIME == 0)) {
        emit shouldPromptForTestimonial();
    }
} 