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
     * @name Singleton Access
     * @brief Provides access to the singleton instance of TestimonialManager.
     * @details Ensures that only one instance of TestimonialManager exists throughout the application.
     */
    /** @{ */
    static TestimonialManager& getInstance();                       ///< Returns a reference to the singleton TestimonialManager instance.
    /** @} */
    
    /**
     * @name Core Testimonial Operations
     * @brief Core testimonial management functions.
     * @details These methods allow adding new testimonials, retrieving satisfactory ones for display,
     *          and checking if a specific user has already submitted a testimonial.
     */
    /** @{ */
    void addTestimonial(const Testimonial& testimonial);            ///< Adds a new testimonial to the manager and persists it.
    QVector<Testimonial> getSatisfactoryTestimonials() const;       ///< Returns a vector of testimonials marked as satisfactory.
    bool hasUserGivenTestimonial(const QString& username) const;    ///< Checks if a user with the given username has already submitted a testimonial.
    /** @} */
    
    /**
     * @name User Prompt Preferences
     * @brief User preference management for testimonial prompts.
     * @details These methods handle the "do not show again" preference for testimonial prompts
     *          on a per-user basis.
     */
    /** @{ */
    void setDoNotShowAgain(const QString& username, bool value);    ///< Sets the "do not show again" preference for a user.
    bool getDoNotShowAgain(const QString& username) const;          ///< Retrieves the "do not show again" preference for a user.
    /** @} */
    
    /**
     * @name Activity Time Tracking
     * @brief Time tracking control for testimonial prompts.
     * @details These methods start and stop the timer that tracks user activity,
     *          which is used to determine when to prompt for a testimonial.
     */
    /** @{ */
    void startTrackingTime();                                       ///< Starts the timer for tracking user activity time.
    void stopTrackingTime();                                        ///< Stops the timer for tracking user activity time.
    /** @} */
    
signals:
    /**
     * @name User Interaction Signals
     * @brief Signal emitted when conditions are met to prompt the user for a testimonial.
     * @details This signal is typically connected to a UI element that will display the prompt.
     */
    /** @{ */
    void shouldPromptForTestimonial();                              ///< Emitted to prompt the user for a testimonial.
    /** @} */

private slots:
    /**
     * @name API Response Slots
     * @brief API client response handlers.
     * @details These private slots are connected to signals from the ApiClient
     *          to process the results of network requests related to testimonials.
     */
    /** @{ */
    void onGoodGetResponse(const QString& json);                    ///< Slot called when a GET request for testimonials succeeds.
    void onBadGetResponse(const QString& error);                    ///< Slot called when a GET request for testimonials fails.
    void onGoodPostResponse();                                      ///< Slot called when a POST request to save testimonials succeeds.
    void onBadPostResponse(const QString& error);                   ///< Slot called when a POST request to save testimonials fails.
    /** @} */
    
private:
    /**
     * @name Singleton Constructor/Destructor
     * @brief Private constructor and destructor for the singleton pattern.
     * @details Ensures that TestimonialManager cannot be instantiated directly from outside the class.
     */
    /** @{ */
    TestimonialManager();                                           ///< Private constructor to enforce singleton pattern. Initializes API connections and timer.
    ~TestimonialManager();                                          ///< Private destructor. Saves testimonials before destruction.
    /** @} */
    
    /**
     * @name Internal Logic
     * @brief Internal data persistence and prompt logic.
     * @details These methods handle the loading and saving of testimonial data (now via API)
     *          and the logic for checking if a testimonial prompt should be displayed.
     */
    /** @{ */
    void loadTestimonials();                                        ///< Loads testimonials (now primarily via API client in constructor).
    void saveTestimonials();                                        ///< Saves all current testimonials (via API client).
    void checkTimeAndPrompt();                                      ///< Checks accumulated user time and emits `shouldPromptForTestimonial` if criteria are met.
    /** @} */

    /**
     * @name Member Data
     * @brief Private member variables for TestimonialManager.
     * @details These members store testimonials, manage timing, user preferences, and utility objects.
     */
    /** @{ */
    QVector<Testimonial> m_testimonials;                            ///< In-memory storage for all loaded testimonials.
    QTimer* m_trackingTimer;                                        ///< Timer used to periodically check if a testimonial prompt is needed.
    QHash<QString, bool> m_doNotShowAgain;                          ///< Stores user preferences for not showing the testimonial prompt again. Key is username.
    QHash<QString, int> m_userTimeTracking;                         ///< Tracks accumulated active time for each user in minutes. Key is username.

    ApiClient client;                                               ///< API client instance for network communication.
    Parser parse;                                                   ///< Parser instance for JSON serialization/deserialization.
    
    // timing constants for testimonial prompts
    static const int INITIAL_PROMPT_TIME = 30 * 60;                 ///< Time in seconds before the first testimonial prompt (30 minutes).
    static const int REPEAT_PROMPT_TIME = 60 * 60;                  ///< Time in seconds for subsequent testimonial prompts if not dismissed (1 hour).
    /** @} */
};

#endif // TESTIMONIALMANAGER_H
