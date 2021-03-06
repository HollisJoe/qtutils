#include "cpersistentwindow.h"

#include "../settings/csettings.h"

DISABLE_COMPILER_WARNINGS
#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QStyle>
RESTORE_COMPILER_WARNINGS

#define GEOMETRY_KEY (_settingsPath + "_geometry")
#define STATE_KEY (_settingsPath + "_state")

CPersistenceEnabler::CPersistenceEnabler(const QString& widgetSettingsPath, QObject* parent) : QObject(parent), _settingsPath(widgetSettingsPath)
{
}

bool CPersistenceEnabler::eventFilter(QObject* watched, QEvent* e)
{
	if (!_windowStateRestored && e->type() == QEvent::Show)
	{
		_windowStateRestored = true;

		auto widget = static_cast<QWidget*>(watched);
		auto window = dynamic_cast<QMainWindow*>(watched);
		CSettings s;

		if (!widget->restoreGeometry(s.value(GEOMETRY_KEY).toByteArray()) || !window || !window->restoreState(s.value(STATE_KEY).toByteArray()))
			window->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, QApplication::desktop()->availableGeometry().size() / 2, QApplication::desktop()->availableGeometry()));
	}
	else if (e->type() == QEvent::Close)
	{
		auto widget = static_cast<QWidget*>(watched);
		auto window = dynamic_cast<QMainWindow*>(watched);
		CSettings s;

		s.setValue(GEOMETRY_KEY, widget->saveGeometry());
		if (window)
			s.setValue(STATE_KEY, window->saveState());
	}

	return QObject::eventFilter(watched, e);
}
