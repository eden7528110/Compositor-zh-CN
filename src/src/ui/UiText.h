#pragma once
#include <QString>
class QMenuBar;
class QMenu;
class QWidget;
namespace compositor::ui {
// Display-only Chinese translation. Command lookup keys in CommandRegistry
// deliberately stay English; only rendered text passes through here.
QString zh(const QString& english);
QString zh(const char* english);
// Narrow overload for APIs that take const char* (e.g. history labels).
const char* zhc(const QString& english);
const char* zhc(const char* english);

// Creates a menu whose title is rendered in Chinese while the English title is
// retained on the "commandMenu" property so command lookup keeps working.
QMenu* addCommandMenu(QMenuBar* bar, const QString& englishTitle);
QMenu* addCommandMenu(QMenu* parent, const QString& englishTitle);
}