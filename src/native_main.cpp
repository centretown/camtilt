#ifndef ARDUINO
#include "Director.h"
#include "ServoActor.h"
#include "CamActor.h"

void display(Director *dir)
{
    for (size_t i = 0; i < dir->length; i++)
    {
        printf("%s: ", dir->list[i]->id);
        dir->list[i]->act(i);
    }
}

void testDirector()
{
    sensor_t theSensor;
    sensor_t *sensor = &theSensor;
    CamActor::initializeCamActors(sensor);
    printf("cam actors count: %lu", CamActor::camActorCount);

    Director* dir = Director::getDirector();
    dir->allocate(CamActor::camActorCount + 4);
    dir->add((Actor **)servoActors, 4);

    dir->add((Actor **)CamActor::camActors, CamActor::camActorCount);
    display(dir);
    printf("\n");

    dir->sort();
    display(dir);

    printf("\n");
    dir->find("hmirror")->act(0);
    dir->find("brightness")->act(1);
    dir->find("move")->act(20);
    dir->find("special_effect")->act(0);
    dir->find("angle")->act(180);
    dir->find("speed")->act(40);
    int err = dir->find("spud")->act(40);
    printf("err=%d\n", err);
}

int main(int argc, char **argv)
{
    testDirector();
}
#endif // ARDUINO
