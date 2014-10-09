#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QTextStream>

QString ReadValidLine(QTextStream &in);

int fat(int n);
float binomial(int n, int i);
float bernstein(float u, int n, int i);

#endif // COMMON_H
