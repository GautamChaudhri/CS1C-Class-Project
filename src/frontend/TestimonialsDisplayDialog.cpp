#include "TestimonialsDisplayDialog.h"
#include "../backend/TestimonialManager.h"
#include "TestimonialDialog.h"
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QFrame>

TestimonialsDisplayDialog::TestimonialsDisplayDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Customer Testimonials");
    setMinimumSize(400, 300);
    
    // main layout
    auto mainLayout = new QVBoxLayout(this);
    
    // add new testimonial button
    auto addButton = new QPushButton("Share Your Experience");
    connect(addButton, &QPushButton::clicked, this, [this]() {
        TestimonialDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            refreshTestimonials();
        }
    });
    mainLayout->addWidget(addButton);
    
    // scrollable area for testimonials
    auto scrollArea = new QScrollArea;
    auto scrollWidget = new QWidget;
    m_testimonialsLayout = new QVBoxLayout(scrollWidget);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);
    
    // close button
    auto closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeButton);
    
    // load testimonials
    refreshTestimonials();
}

// update testimonials display
void TestimonialsDisplayDialog::refreshTestimonials() {
    // clear existing testimonials
    QLayoutItem* item;
    while ((item = m_testimonialsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    
    // add each testimonial to display
    auto testimonials = TestimonialManager::getInstance().getSatisfactoryTestimonials();
    
    if (testimonials.isEmpty()) {
        auto noTestimonialsLabel = new QLabel("No Testimonials Yet - Be The First To Share!");
        noTestimonialsLabel->setAlignment(Qt::AlignCenter);
        m_testimonialsLayout->addWidget(noTestimonialsLabel);
    }
    
    for (const auto& testimonial : testimonials) {
        auto frame = new QFrame;
        frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
        
        auto layout = new QVBoxLayout(frame);
        
        // show author and timestamp
        auto headerLabel = new QLabel(QString("From: %1 - %2")
            .arg(testimonial.getAuthor())
            .arg(testimonial.getTimestamp().toString("MM/dd/yyyy")));
        headerLabel->setStyleSheet("font-weight: bold;");
        layout->addWidget(headerLabel);
        
        // show testimonial content
        auto contentLabel = new QLabel(testimonial.getContent());
        contentLabel->setWordWrap(true);
        layout->addWidget(contentLabel);
        
        m_testimonialsLayout->addWidget(frame);
    }
    
    // add stretch at end
    m_testimonialsLayout->addStretch();
} 