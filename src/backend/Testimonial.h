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
     * @name Constructor
     * @brief Constructs a Testimonial object.
     * @details Initializes a new testimonial with the provided author, content, and guest status.
     *          The timestamp is automatically set to the current date and time, and
     *          `isSatisfactory` defaults to true.
     */
    /** @{ */
    Testimonial(const QString& author = "", const QString& content = "", bool isGuest = true); ///< Constructor with optional parameters.
    /** @} */
    
    /**
     * @name Getters
     * @brief Public getters for accessing testimonial data.
     * @details These methods provide read-only access to the private member variables
     *          of the Testimonial object.
     */
    /** @{ */
    QString getAuthor() const;          ///< Returns the author of the testimonial.
    QString getContent() const;         ///< Returns the content of the testimonial.
    QDateTime getTimestamp() const;     ///< Returns the timestamp when the testimonial was submitted.
    bool isGuest() const;               ///< Returns true if the author is a guest, false otherwise.
    bool isSatisfactory() const;        ///< Returns true if the testimonial is marked as satisfactory for display.
    /** @} */
    
    /**
     * @name Setters
     * @brief Public setter for the satisfaction flag.
     * @details This method allows modification of the `m_isSatisfactory` flag,
     *          typically used for moderation purposes.
     */
    /** @{ */
    void setIsSatisfactory(bool value); ///< Sets the satisfactory status of the testimonial.
    /** @} */
    
    /**
     * @name JSON Conversion
     * @brief JSON conversion methods for database storage and retrieval.
     * @details These static and member methods handle the serialization of a Testimonial
     *          object to a QJsonObject and deserialization from a QJsonObject.
     */
    /** @{ */
    QJsonObject toJson() const;         ///< Converts the Testimonial object to a QJsonObject.
    static Testimonial fromJson(const QJsonObject& json); ///< Creates a Testimonial object from a QJsonObject.
    /** @} */

private:
    /**
     * @name Member Data
     * @brief Private member variables storing testimonial attributes.
     * @details These variables store the core information for each testimonial.
     */
    /** @{ */
    QString m_author;                   ///< Name of the person giving the testimonial.
    QString m_content;                  ///< Actual testimonial text.
    QDateTime m_timestamp;              ///< Timestamp of when the testimonial was submitted.
    bool m_isGuest;                     ///< Flag indicating if the author is a guest or a registered user.
    bool m_isSatisfactory;              ///< Flag indicating if the testimonial is deemed satisfactory for display (e.g., after moderation).
    /** @} */
};

#endif // TESTIMONIAL_H
