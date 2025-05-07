#ifndef COLUMNEDITDELEGATE_H
#define COLUMNEDITDELEGATE_H

#include <QStyledItemDelegate>

/**
 * @brief The ColumnEditDelegate class
 */
class ColumnEditDelegate : public QStyledItemDelegate
{
public:
    /**
     * @brief ColumnEditDelegate Constructor
     * @param parent
     */
    ColumnEditDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    /**
     * @brief createEditor
     * @param parent
     * @param option
     * @param index
     * @return
     */
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        if (index.column() != 1 || !canEdit)
        {
            return nullptr;  // Only allows editing in column 1
        }

        return QStyledItemDelegate::createEditor(parent, option, index);
    }

    /**
     * @brief setCanEdit
     * @param edit
     */
    void setCanEdit(bool edit)
    {
        canEdit = edit;
    }


private:
    bool canEdit = false;  ///< Flag to control whether editing is allowed
};

#endif // COLUMNEDITDELEGATE_H
