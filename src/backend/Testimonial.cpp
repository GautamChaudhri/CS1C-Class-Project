#include "Testimonial.h"

Testimonial::Testimonial(const QString& author, const QString& content, bool isGuest)
    : m_author(author)
    , m_content(content)
    , m_timestamp(QDateTime::currentDateTime())
    , m_isGuest(isGuest)
    , m_isSatisfactory(true) // start as satisfactory until moderated (this is not really used but meant to be for bad/inapprpriate reviews)
{}

// convert testimonial to json for saving
QJsonObject Testimonial::toJson() const {
    QJsonObject json;
    json["author"] = m_author;
    json["content"] = m_content;
    json["timestamp"] = m_timestamp.toString(Qt::ISODate);
    json["isGuest"] = m_isGuest;
    json["isSatisfactory"] = m_isSatisfactory;
    return json;
}

// create testimonial from json when loading
Testimonial Testimonial::fromJson(const QJsonObject& json) {
    Testimonial testimonial;
    testimonial.m_author = json["author"].toString();
    testimonial.m_content = json["content"].toString();
    testimonial.m_timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);
    testimonial.m_isGuest = json["isGuest"].toBool();
    testimonial.m_isSatisfactory = json["isSatisfactory"].toBool();
    return testimonial;
} 
