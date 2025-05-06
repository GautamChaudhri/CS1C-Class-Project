#ifndef TESTIMONIAL_H
#define TESTIMONIAL_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

/**
 * @brief Represents a user testimonial.
 * @details This class encapsulates the data for a testimonial, including the author's name,
 *          the content of the testimonial, a timestamp, whether the author is a guest,
 *          and a flag indicating if the testimonial is satisfactory for display.
 *          It also provides methods for converting testimonial data to and from JSON format.
 */
class Testimonial {
public:
    /**
     * @brief Constructs a Testimonial object.
     * @details Initializes a new testimonial with the provided author, content, and guest status.
     *          The timestamp is automatically set to the current date and time, and
     *          `isSatisfactory` defaults to true.
     * @param author The name of the person giving the testimonial. Defaults to an empty string.
     * @param content The actual text of the testimonial. Defaults to an empty string.
     * @param isGuest True if the author is a guest, false if registered. Defaults to true.
     */
    Testimonial(const QString& author = "", const QString& content = "", bool isGuest = true);
    
    /**
     * @brief Public getters for accessing testimonial data.
     * @details These methods provide read-only access to the private member variables
     *          of the Testimonial object.
     */
    QString getAuthor() const;          /** @brief Returns the author of the testimonial. */
    QString getContent() const;         /** @brief Returns the content of the testimonial. */
    QDateTime getTimestamp() const;     /** @brief Returns the timestamp when the testimonial was submitted. */
    bool isGuest() const;               /** @brief Returns true if the author is a guest, false otherwise. */
    bool isSatisfactory() const;        /** @brief Returns true if the testimonial is marked as satisfactory for display. */
    
    /**
     * @brief Public setter for the satisfaction flag.
     * @details This method allows modification of the `m_isSatisfactory` flag,
     *          typically used for moderation purposes.
     */
    void setIsSatisfactory(bool value); /** @brief Sets the satisfactory status of the testimonial. */
    
    /**
     * @brief JSON conversion methods for database storage and retrieval.
     * @details These static and member methods handle the serialization of a Testimonial
     *          object to a QJsonObject and deserialization from a QJsonObject.
     */
    QJsonObject toJson() const;         /** @brief Converts the Testimonial object to a QJsonObject. */
    static Testimonial fromJson(const QJsonObject& json); /** @brief Creates a Testimonial object from a QJsonObject. */

private:
    QString m_author;                   /**< @brief Name of the person giving the testimonial. */
    QString m_content;                  /**< @brief Actual testimonial text. */
    QDateTime m_timestamp;              /**< @brief Timestamp of when the testimonial was submitted. */
    bool m_isGuest;                    /**< @brief Flag indicating if the author is a guest or a registered user. */
    bool m_isSatisfactory;             /**< @brief Flag indicating if the testimonial is deemed satisfactory for display (e.g., after moderation). */
};

#endif // TESTIMONIAL_H 
