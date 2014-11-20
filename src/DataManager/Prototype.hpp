#pragma once

#include <QtCore>

class Prototype {
public:
	Prototype() = default;

	QVariant getProperty(const QString &key) const;
	void setProperty(const QString &key, const QVariant &value);

private:
	QMap <QString, QVariant> properties;

	friend QDataStream &operator<<(QDataStream &out, const Prototype &prototype);
	friend QDataStream &operator>>(QDataStream &in, Prototype &prototype);
};