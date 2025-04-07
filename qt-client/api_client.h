#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ShapeApiClient : public QObject {
    Q_OBJECT
public:
    explicit ShapeApiClient(QObject* parent = nullptr)
      : QObject(parent),
        manager(new QNetworkAccessManager(this))
    {}

    /// Fetch all shapes from GET /shapes
    void fetchAllShapes() {
        QNetworkRequest req(QUrl("http://localhost:8080/shapes"));
        auto* reply = manager->get(req);
        connect(reply, &QNetworkReply::finished,
                this, &ShapeApiClient::onFetchAllShapesFinished);
    }

signals:
    /// Emitted when the raw JSON comes back
    void shapesJsonReceived(const QString& json);

    /// Emitted on network or HTTP error
    void errorOccurred(const QString& errorString);

private slots:
    void onFetchAllShapesFinished() {
        auto* reply = qobject_cast<QNetworkReply*>(sender());
        if (!reply) return;

        if (reply->error() == QNetworkReply::NoError) {
            QByteArray bytes = reply->readAll();
            QString json = QString::fromUtf8(bytes);
            emit shapesJsonReceived(json);
        } else {
            emit errorOccurred(reply->errorString());
        }

        reply->deleteLater();
    }

private:
    QNetworkAccessManager* manager;
};

#endif // API_CLIENT_H