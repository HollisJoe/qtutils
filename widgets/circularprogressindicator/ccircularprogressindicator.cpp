// Stolen from https://github.com/yageek/CCircularProgressIndicator.git

#include "ccircularprogressindicator.h"

#include <QPainter>

CCircularProgressIndicator::CCircularProgressIndicator(QWidget* parent)
	: QWidget(parent),
	  m_angle(0),
	  m_timerId(-1),
	  m_delay(40),
	  m_displayedWhenStopped(false),
	  m_color(Qt::black)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setFocusPolicy(Qt::NoFocus);
}

bool CCircularProgressIndicator::isAnimated () const
{
	return (m_timerId != -1);
}

void CCircularProgressIndicator::setDisplayedWhenStopped(bool state)
{
	m_displayedWhenStopped = state;

	update();
}

bool CCircularProgressIndicator::isDisplayedWhenStopped() const
{
	return m_displayedWhenStopped;
}

void CCircularProgressIndicator::startAnimation()
{
	m_angle = 0;

	if (m_timerId == -1)
		m_timerId = startTimer(m_delay);
}

void CCircularProgressIndicator::stopAnimation()
{
	if (m_timerId != -1)
		killTimer(m_timerId);

	m_timerId = -1;

	update();
}

void CCircularProgressIndicator::setAnimationDelay(int delay)
{
	if (m_timerId != -1)
		killTimer(m_timerId);

	m_delay = delay;

	if (m_timerId != -1)
		m_timerId = startTimer(m_delay);
}

void CCircularProgressIndicator::setColor(const QColor & color)
{
	m_color = color;

	update();
}

QSize CCircularProgressIndicator::sizeHint() const
{
	return QSize(20,20);
}

int CCircularProgressIndicator::heightForWidth(int w) const
{
	return w;
}

void CCircularProgressIndicator::timerEvent(QTimerEvent * /*event*/)
{
	m_angle = (m_angle+30)%360;

	update();
}

void CCircularProgressIndicator::paintEvent(QPaintEvent * /*event*/)
{
	if (!m_displayedWhenStopped && !isAnimated())
		return;

	const int width = std::min(this->width(), this->height());

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);

	const int outerRadius = (width-1) / 2;
	const int innerRadius = (int)((width-1)*0.5f*0.38f);

	const int capsuleHeight = outerRadius - innerRadius;
	const int capsuleWidth  = (int)((width > 32 ) ? capsuleHeight *.23f : capsuleHeight *.35f);
	const int capsuleRadius = capsuleWidth / 2;

	for (int i = 0; i < 12; i++)
	{
		QColor color = m_color;
		color.setAlphaF(1.0f - i / 12.0f);
		p.setPen(Qt::NoPen);
		p.setBrush(color);
		p.save();
		p.translate(rect().center());
		p.rotate(m_angle - i*30.0f);
		p.drawRoundedRect(-capsuleWidth / 2, -(innerRadius+capsuleHeight), capsuleWidth, capsuleHeight, capsuleRadius, capsuleRadius);
		p.restore();
	}
}
