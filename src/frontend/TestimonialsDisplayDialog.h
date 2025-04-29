#ifndef TESTIMONIALSDISPLAYDIALOG_H
#define TESTIMONIALSDISPLAYDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include "TestimonialDialog.h"

// dialog to show all testimonials
class TestimonialsDisplayDialog : public QDialog {
    Q_OBJECT
    
public:
    explicit TestimonialsDisplayDialog(QWidget* parent = nullptr);
    
private:
    void refreshTestimonials();
    QVBoxLayout* m_testimonialsLayout;
};

#endif // TESTIMONIALSDISPLAYDIALOG_H 