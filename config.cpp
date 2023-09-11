#include "config.h"

Config::Config(QObject *parent) : QObject{parent} {}

Config::Config(const Config &other)
    : m_endpoint(other.m_endpoint), m_target(other.m_target),
      m_desc(other.m_desc), m_font(other.m_font), m_color(other.m_color),
      m_background(other.m_background), m_button(other.m_button) {}

Config &Config::operator=(const Config &other) {
  if (this != &other) {
    m_endpoint = other.m_endpoint;
    m_target = other.m_target;
    m_desc = other.m_desc;
    m_font = other.m_font;
    m_color = other.m_color;
    m_background = other.m_background;
    m_button = other.m_button;
  }
  return *this;
}

QString Config::endpoint() const { return m_endpoint; }

QString Config::target() const { return m_target; }

QString Config::desc() const { return m_desc; }

QColor Config::color() const { return m_color; }

QFont Config::font() const { return m_font; }

QColor Config::background() const { return m_background; }

QColor Config::button() const { return m_button; }

void Config::setEndpoint(const QString &newEndpoint) {
  m_endpoint = newEndpoint;
}

void Config::setTarget(const QString &newTarget) { m_target = newTarget; }

void Config::setDesc(const QString &newDesc) { m_desc = newDesc; }

void Config::setFont(const QFont &newFont) { m_font = newFont; }

void Config::setColor(const QColor &newColor) { m_color = newColor; }

void Config::setBackground(const QColor &newBackground) {
  m_background = newBackground;
}

void Config::setButton(const QColor &newButton) { m_button = newButton; }
