/**
 * @file TestimonialsDisplayDialog.h
 * @brief Defines the TestimonialsDisplayDialog class for showing customer testimonials.
 * @details This dialog displays a list of testimonials and provides an option
 *          for users to submit their own experiences.
 */
#ifndef TESTIMONIALSDISPLAYDIALOG_H
#define TESTIMONIALSDISPLAYDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QScrollArea> // Included for context, used in .cpp
#include <QPushButton> // Included for context, used in .cpp
#include <QLabel>      // Included for context, used in .cpp
#include <QFrame>      // Included for context, used in .cpp
#include "TestimonialDialog.h"

/**
 * @brief The TestimonialsDisplayDialog class provides a UI to display customer testimonials.
 * @details This dialog fetches and displays testimonials from the TestimonialManager.
 *          It includes a button to open the TestimonialDialog for new submissions
 *          and dynamically updates the displayed list.
 */
class TestimonialsDisplayDialog : public QDialog {
    Q_OBJECT
    
public:
    /**
     * @brief Constructs a TestimonialsDisplayDialog.
     * @param parent The parent widget of this dialog.
     */
    explicit TestimonialsDisplayDialog(QWidget* parent = nullptr);
    
private slots:
    // No explicit slots are defined in the header, but a lambda is used in the .cpp
    // for the "Share Your Experience" button.

private:
    /**
     * @brief Refreshes the displayed list of testimonials.
     * @details Clears the current list and repopulates it with testimonials
     *          retrieved from the TestimonialManager.
     */
    void refreshTestimonials();

    /**
     * @brief Private member variables representing UI components.
     * @details These members store pointers to the layout managing the display of testimonials.
     */
    QVBoxLayout* m_testimonialsLayout; ///< Layout for arranging individual testimonial widgets.
};

#endif // TESTIMONIALSDISPLAYDIALOG_H
