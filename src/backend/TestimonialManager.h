#ifndef TESTIMONIALMANAGER_H
#define TESTIMONIALMANAGER_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QDebug>

#include "Testimonial.h"
#include "ApiClient.h"
#include "Parser.h"

class TestimonialManager : public QObject {
    Q_OBJECT
public:
    static TestimonialManager& getInstance();
    
    // testimonial management functions
    void addTestimonial(const Testimonial& testimonial);
    QVector<Testimonial> getSatisfactoryTestimonials() const;
    bool hasUserGivenTestimonial(const QString& username) const;
    
    // handle do not show again preference
    void setDoNotShowAgain(const QString& username, bool value);
    bool getDoNotShowAgain(const QString& username) const;
    
    // time tracking functions
    void startTrackingTime();
    void stopTrackingTime();
    
signals:
    void shouldPromptForTestimonial();

private slots:
    // Callbacks for API client responses
    void onGoodGetResponse(const QString& json);
    void onBadGetResponse(const QString& error);
    void onGoodPostResponse();
    void onBadPostResponse(const QString& error);
    
private:
    TestimonialManager();
    ~TestimonialManager();
    
    // database operations
    void loadTestimonials();
    void saveTestimonials();
    void checkTimeAndPrompt();
    
    QVector<Testimonial> m_testimonials;          // stored testimonials
    QTimer* m_trackingTimer;                     // tracks user time
    QHash<QString, bool> m_doNotShowAgain;       // stores user preferences
    QHash<QString, int> m_userTimeTracking;      // tracks time per user

    ApiClient client;
    Parser parse;
    
    // timing constants
    static const int INITIAL_PROMPT_TIME = 30 * 60;   // 30 min in seconds
    static const int REPEAT_PROMPT_TIME = 60 * 60;    // 1 hour in seconds
};

#endif // TESTIMONIALMANAGER_H 
