/**
 * @file ToolTextButton.h
 * @brief Flat text button used inside ToolBarWidget.
 *
 * Inherits QPushButton with a flat appearance and a pointing-hand cursor.
 * All visual styling is delegated to @c style.qss via the @c ToolTextButton
 * type selector — there are no inline stylesheets in this class.
 *
 * Each button carries a ButtonType enum value that identifies which menu
 * it represents, allowing controllers to act on the type rather than the
 * display text.
 */

#ifndef TOOLTEXTBUTTON_H
#define TOOLTEXTBUTTON_H

#include <QPushButton>

/**
 * @class ToolTextButton
 * @brief A flat, labelled menu-bar button that opens a QMenu on click.
 *
 * The associated QMenu is set externally via the inherited
 * @c QPushButton::setMenu() method.
 *
 * @see ToolBarWidget — creates and attaches menus to each button.
 */
class ToolTextButton : public QPushButton {
    Q_OBJECT

public:
    /**
     * @brief Identifies the logical role of each menu-bar entry.
     *
     * Used by controllers to dispatch actions without relying on
     * the translated display text.
     */
    enum ButtonType {
        Files,         ///< "Files" menu — file operations (copy, delete, …).
        Mark,          ///< "Mark" menu — selection operations.
        Commands,      ///< "Commands" menu — search, pack, compare, …
        Net,           ///< "Net" menu — FTP / network connections.
        Show,          ///< "Show" menu — view mode and sort order.
        Configuration, ///< "Configuration" menu — application settings.
        Start,         ///< "Start" menu — user-defined programs.
        Help           ///< "Help" menu — documentation and about.
    };

    /**
     * @brief Constructs the button with the given label and logical type.
     * @param text  The visible button label (e.g. "Files").
     * @param type  The logical role; used for programmatic identification.
     * @param parent Optional Qt parent widget.
     */
    explicit ToolTextButton(const QString &text, ButtonType type,
                            QWidget *parent = nullptr);

    /**
     * @brief Returns the logical type assigned at construction time.
     * @return ButtonType enum value.
     */
    ButtonType getType() const;

private:
    ButtonType m_type; ///< Logical role of this button.
};

#endif
