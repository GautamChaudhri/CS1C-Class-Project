#ifndef TESTIMONIAL_H
#define TESTIMONIAL_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class Testimonial {
public:
    Testimonial(const QString& author = "", const QString& content = "", bool isGuest = true);
    
    // getters for testimonial data
    QString getAuthor() const { return m_author; }
    QString getContent() const { return m_content; }
    QDateTime getTimestamp() const { return m_timestamp; }
    bool isGuest() const { return m_isGuest; }
    bool isSatisfactory() const { return m_isSatisfactory; }
    
    // setter for satisfaction flag
    void setIsSatisfactory(bool value) { m_isSatisfactory = value; }
    
    // json conversion for database storage
    QJsonObject toJson() const;
    static Testimonial fromJson(const QJsonObject& json);

private:
    QString m_author;        // name of person giving testimonial
    QString m_content;       // actual testimonial text
    QDateTime m_timestamp;   // when it was submitted
    bool m_isGuest;         // if they're a guest or registered
    bool m_isSatisfactory;   // if we should show this one
};

#endif // TESTIMONIAL_H 
