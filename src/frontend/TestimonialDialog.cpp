#include "TestimonialDialog.h"
#include "../backend/TestimonialManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

TestimonialDialog::TestimonialDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Share Your Experience");
    
    // setup main layout
    auto layout = new QVBoxLayout(this);
    
    // name input area
    auto authorLayout = new QHBoxLayout;
    authorLayout->addWidget(new QLabel("Name:"));
    m_authorEdit = new QLineEdit;
    authorLayout->addWidget(m_authorEdit);
    layout->addLayout(authorLayout);
    
    // testimonial input area
    layout->addWidget(new QLabel("Your Experience:"));
    m_contentEdit = new QTextEdit;
    layout->addWidget(m_contentEdit);
    
    // do not show again option
    m_doNotShowAgain = new QCheckBox("Do Not Show This Prompt Again");
    layout->addWidget(m_doNotShowAgain);
    
    // submit/cancel buttons
    auto buttonLayout = new QHBoxLayout;
    auto submitButton = new QPushButton("Submit");
    auto cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(submitButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);
    
    // connect buttons
    connect(submitButton, &QPushButton::clicked, this, &TestimonialDialog::onSubmit);
    connect(cancelButton, &QPushButton::clicked, this, &TestimonialDialog::onCancel);
}

// handle testimonial submission
void TestimonialDialog::onSubmit() {
    QString author = m_authorEdit->text();
    QString content = m_contentEdit->toPlainText();
    
    // only add if they wrote something
    if (!content.isEmpty()) {
        Testimonial testimonial(author, content, true);
        TestimonialManager::getInstance().addTestimonial(testimonial);
    }
    
    // save do not show preference
    if (m_doNotShowAgain->isChecked()) {
        TestimonialManager::getInstance().setDoNotShowAgain("", true);
    }
    
    accept();
}

// handle cancellation
void TestimonialDialog::onCancel() {
    if (m_doNotShowAgain->isChecked()) {
        TestimonialManager::getInstance().setDoNotShowAgain("", true);
    }
    reject();
} 