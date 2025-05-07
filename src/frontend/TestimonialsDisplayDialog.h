#ifndef TESTIMONIALSDISPLAYDIALOG_H
#define TESTIMONIALSDISPLAYDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include "TestimonialDialog.h"

/**
 * @brief The TestimonialsDisplayDialog class
 *
 * @details dialog to show all testimonials
 */
class TestimonialsDisplayDialog : public QDialog {
    Q_OBJECT
    
public:
    /**
     * @brief TestimonialsDisplayDialog Constructor
     * @param parent - QWidget of which this class belongs
     *
     * @details
     */
    explicit TestimonialsDisplayDialog(QWidget* parent = nullptr);
    
private:
    /**
     * @brief refreshTestimonials - Refreshes the testimonials
     */
    void refreshTestimonials();
    QVBoxLayout* m_testimonialsLayout; ///< Vertical box layout for the testimonials
};

#endif // TESTIMONIALSDISPLAYDIALOG_H 
