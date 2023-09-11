#ifndef CONFIG_H
#define CONFIG_H

#include <QColor>
#include <QFont>
#include <QObject>

class Config : public QObject {
  Q_OBJECT
public:
  explicit Config(QObject *parent = nullptr);
  Config(const Config &);
  Config &operator=(const Config &);

  QString endpoint() const;
  QString target() const;
  QString desc() const;
  QColor color() const;
  QFont font() const;
  QColor background() const;
  QColor button() const;

  void setEndpoint(const QString &newEndpoint);
  void setTarget(const QString &newTarget);
  void setDesc(const QString &newDesc);
  void setFont(const QFont &newFont);
  void setColor(const QColor &newColor);
  void setBackground(const QColor &newBackground);
  void setButton(const QColor &newButton);

private:
  QString m_endpoint;
  QString m_target;
  QString m_desc;
  QFont m_font;
  QColor m_color;
  QColor m_background;
  QColor m_button;
};

#endif // CONFIG_H
