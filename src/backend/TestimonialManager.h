#ifndef TESTIMONIALMANAGER_H
#define TESTIMONIALMANAGER_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QHash>
#include "Testimonial.h"
#include "ApiClient.h"
#include "Parser.h"

/**
 * @brief Manages user testimonials, including storage, retrieval, and prompting logic.
 * @details This class is a singleton that handles all operations related to testimonials.
 *          It interacts with an ApiClient to load and save testimonials from/to a webservice,
 *          tracks user activity time to determine when to prompt for a testimonial,
 *          and manages user preferences regarding these prompts.
 */
class TestimonialManager : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Provides access to the singleton instance of TestimonialManager.
     * @details Ensures that only one instance of TestimonialManager exists throughout the application.
     * @return A reference to the singleton TestimonialManager instance.
     */
    static TestimonialManager& getInstance();
    
    /**
     * @brief Core testimonial management functions.
     * @details These methods allow adding new testimonials, retrieving satisfactory ones for display,
     *          and checking if a specific user has already submitted a testimonial.
     */
    void addTestimonial(const Testimonial& testimonial);              /** @brief Adds a new testimonial to the manager and persists it. */
    QVector<Testimonial> getSatisfactoryTestimonials() const;         /** @brief Returns a vector of testimonials marked as satisfactory. */
    bool hasUserGivenTestimonial(const QString& username) const;      /** @brief Checks if a user with the given username has already submitted a testimonial. */
    
    /**
     * @brief User preference management for testimonial prompts.
     * @details These methods handle the "do not show again" preference for testimonial prompts
     *          on a per-user basis.
     */
    void setDoNotShowAgain(const QString& username, bool value);      /** @brief Sets the "do not show again" preference for a user. */
    bool getDoNotShowAgain(const QString& username) const;            /** @brief Retrieves the "do not show again" preference for a user. */
    
    /**
     * @brief Time tracking control for testimonial prompts.
     * @details These methods start and stop the timer that tracks user activity,
     *          which is used to determine when to prompt for a testimonial.
     */
    void startTrackingTime();                                         /** @brief Starts the timer for tracking user activity time. */
    void stopTrackingTime();                                          /** @brief Stops the timer for tracking user activity time. */
    
signals:
    /**
     * @brief Signal emitted when conditions are met to prompt the user for a testimonial.
     * @details This signal is typically connected to a UI element that will display the prompt.
     */
    void shouldPromptForTestimonial();

private slots:
    /**
     * @brief API client response handlers.
     * @details These private slots are connected to signals from the ApiClient
     *          to process the results of network requests related to testimonials.
     */
    void onGoodGetResponse(const QString& json);                      /** @brief Slot called when a GET request for testimonials succeeds. */
    void onBadGetResponse(const QString& error);                      /** @brief Slot called when a GET request for testimonials fails. */
    void onGoodPostResponse();                                        /** @brief Slot called when a POST request to save testimonials succeeds. */
    void onBadPostResponse(const QString& error);                     /** @brief Slot called when a POST request to save testimonials fails. */
    
private:
    /**
     * @brief Private constructor and destructor for the singleton pattern.
     * @details Ensures that TestimonialManager cannot be instantiated directly from outside the class.
     */
    TestimonialManager();                                             /** @brief Private constructor to enforce singleton pattern. Initializes API connections and timer. */
    ~TestimonialManager();                                            /** @brief Private destructor. Saves testimonials before destruction. */
    
    /**
     * @brief Internal data persistence and prompt logic.
     * @details These methods handle the loading and saving of testimonial data (now via API)
     *          and the logic for checking if a testimonial prompt should be displayed.
     */
    void loadTestimonials();                                          /** @brief Loads testimonials (now primarily via API client in constructor). */
    void saveTestimonials();                                          /** @brief Saves all current testimonials (via API client). */
    void checkTimeAndPrompt();                                        /** @brief Checks accumulated user time and emits `shouldPromptForTestimonial` if criteria are met. */
    
    QVector<Testimonial> m_testimonials;                              /**< @brief In-memory storage for all loaded testimonials. */
    QTimer* m_trackingTimer;                                          /**< @brief Timer used to periodically check if a testimonial prompt is needed. */
    QHash<QString, bool> m_doNotShowAgain;                            /**< @brief Stores user preferences for not showing the testimonial prompt again. Key is username. */
    QHash<QString, int> m_userTimeTracking;                           /**< @brief Tracks accumulated active time for each user in minutes. Key is username. */

    ApiClient client;                                                 /**< @brief API client instance for network communication. */
    Parser parse;                                                     /**< @brief Parser instance for JSON serialization/deserialization. */
    
    // timing constants for testimonial prompts
    static const int INITIAL_PROMPT_TIME = 30 * 60;                   /**< @brief Time in seconds before the first testimonial prompt (30 minutes). */
    static const int REPEAT_PROMPT_TIME = 60 * 60;                    /**< @brief Time in seconds for subsequent testimonial prompts if not dismissed (1 hour). */
};

#endif // TESTIMONIALMANAGER_H
