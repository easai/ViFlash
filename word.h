#ifndef WORD_H
#define WORD_H

#include <QObject>
#include <QVariantMap>

using namespace std;

class Word : public QObject {
  Q_OBJECT
public:
  explicit Word(QObject *parent, const QVariantMap &map);
  explicit Word(QObject *parent);
  QString getValue(const QString &key) const;
  operator QString() const;
  Word(const Word &);
  Word &operator=(const Word &);

  void setDat(const QVariantMap &newDat);

  private:
  QVariantMap m_dat;
};

#endif // WORD_H
