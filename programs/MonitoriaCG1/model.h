#ifndef MODEL_H
#define MODEL_H

#include <QString>

class Model
{
public:
    Model();

    void Draw() const;
    void Load(QString filename);
};

#endif // MODEL_H
