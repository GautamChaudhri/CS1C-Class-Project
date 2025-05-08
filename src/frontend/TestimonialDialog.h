/**
 * @file TestimonialDialog.h
 * @brief Defines the TestimonialDialog class for submitting user testimonials.
 * @details This dialog allows users to enter their name and testimonial content,
 *          and choose whether to be prompted again in the future.
 */
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

/**
 * @brief The TestimonialDialog class provides a user interface for submitting testimonials.
 * @details This dialog includes fields for the author's name, the testimonial content,
 *          and an option to prevent future prompts. It handles the submission and
 *          cancellation of testimonials.
 */
class TestimonialDialog : public QDialog {
    Q_OBJECT
    
public:
    /**
     * @brief Constructs a TestimonialDialog.
     * @param parent The parent widget of this dialog.
     */
    explicit TestimonialDialog(QWidget* parent = nullptr);
    
private slots:
    /**
     * @name Event Handling Slots
     * @brief Slots for handling UI events.
     * @details These slots are connected to button clicks within the dialog.
     */
    /** @{ */
    void onSubmit();        ///< Handles the submission of a new testimonial.
    void onCancel();        ///< Handles the cancellation of the testimonial submission.
    /** @} */
    
private:
    /**
     * @name UI Elements
     * @brief Private member variables representing UI components.
     * @details These members store pointers to the various input fields and controls
     *          used within the testimonial dialog.
     */
    /** @{ */
    QLineEdit* m_authorEdit;        ///< Input field for the author's name.
    QTextEdit* m_contentEdit;       ///< Input field for the testimonial content.
    QCheckBox* m_doNotShowAgain;    ///< Checkbox to control future display of the prompt.
    /** @} */
};

#endif // TESTIMONIALDIALOG_H
