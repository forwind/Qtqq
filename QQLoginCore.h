#ifndef QTQQ_QQLOGINCORE_H
#define QTQQ_QQLOGINCORE_H

#include <QTcpSocket>

#include "types.h"

class QByteArray;
class QTcpSocket;

#include <QObject>

class QQLoginCore : public QObject
{
    Q_OBJECT
public:
    enum AccountStatus {kNormal, kExceptionCpaImg};
    enum LoginResult {kIdOrPwdWrong, kAuthcodeWrong, kSucess, kUnknowErr};
    QQLoginCore();
    ~QQLoginCore();

public:
    QPixmap getCapImg();
    void login(QString id, QString pwd, FriendStatus status);
    void login(QString id, QString pwd, FriendStatus status, QString vc);
    AccountStatus checkState(QString id);
    void setFriendInfo(FriendInfo curr_user_info);

signals:
    void sig_loginDone(QQLoginCore::LoginResult result);

private slots:
    void loginRead();
    char getResultState(const QByteArray &array);
    void getLoginInfo(QString ptwebqq);
    void getLoginInfoDone();
    QByteArray getPwMd5(QString pwd);

private:
    QString getLoginStatus() const;
    void getCaptchaImg(QByteArray sum);
    void setupStatus(QString id, QString pwd, FriendStatus status);
    
private:
    FriendInfo curr_user_info_;
    QString check_url_;
    QTcpSocket *fd_;
    QString vc_;
    QByteArray sum_;

    QString id_;
    QString pwd_;
    FriendStatus status_;
};

#endif // QTQQ_QQLOGINCORE_H