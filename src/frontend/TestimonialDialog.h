#ifndef TESTIMONIALDIALOG_H
#define TESTIMONIALDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>

// dialog for submitting new testimonials
class TestimonialDialog : public QDialog {
    Q_OBJECT
    
public:
    explicit TestimonialDialog(QWidget* parent = nullptr);
    
private slots:
    void onSubmit();
    void onCancel();
    
private:
    QLineEdit* m_authorEdit;     // name input
    QTextEdit* m_contentEdit;    // testimonial input
    QCheckBox* m_doNotShowAgain; // checkbox for future prompts
};

#endif // TESTIMONIALDIALOG_H 
