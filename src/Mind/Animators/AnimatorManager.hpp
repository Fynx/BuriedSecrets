/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

#include <QtCore>

class Mind;

/**
 * @class AnimatorManager
 * Creates, triggers and deletes Animators.
 */
class AnimatorManager : public QObject {

Q_OBJECT;
public:
	AnimatorManager(Mind *mind);
	~AnimatorManager();

	bool addObject(QString animator, Object *obj);
	bool removeObject(QString animator, Object *obj);
	bool removeObject(Object *obj);

	/** Timeflow control functions. */
	void pauseGame();
	void resumeGame();

	QVector<QString> getAnimatorsForObject(const Object *obj) const;

private:
	void initAnimators();
	void initTimers();
	void addAnimator(Animator *anim, const QString name, const int interval);

	QMap<int, QVector<Animator *> >intervals;
	QMap<QString, Animator *> animators;
	QVector<QTimer *> timers;
	QSignalMapper signalMapper;

	Mind *mind;

private slots:
	/** Triggers all animators, periodically. */
	void update(const int timeElapsed);
};
