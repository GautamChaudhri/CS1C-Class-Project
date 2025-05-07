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
 * @brief The TestimonialDialog class
 *
 * @details Dialog for setting new testimonials
 */
class TestimonialDialog : public QDialog {
    Q_OBJECT
    
public:
    /**
     * @brief TestimonialDialog Constructor
     * @param parent - QWidget of which this class belongs
     */
    explicit TestimonialDialog(QWidget* parent = nullptr);
    
private slots:
    /**
     * @brief onSubmit - Handles a user submitting a testimonial
     */
    void onSubmit();

    /**
     * @brief onCancel - Handles a user canceling the submission of a new testimonial
     */
    void onCancel();
    
private:
    QLineEdit* m_authorEdit; ///< name input
    QTextEdit* m_contentEdit; ///< testimonial input
    QCheckBox* m_doNotShowAgain; ///< checkbox for future prompts
};

#endif // TESTIMONIALDIALOG_H 
