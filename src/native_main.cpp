#ifndef ARDUINO
#include "base.h"
#include "Director.h"
#include "ServoActor.h"
#include "CamActor.h"
#include "query.h"

#include "ControlHandler.h"

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
    MicroTerm term;
    sensor_t theSensor;
    CamActor::initializeCamActors(&theSensor);
    ServoActor::initializeServoActors(&term);

    printf("cam actions: %lu", CamActor::actorCount);
    printf("servo actions: %lu\n", ServoActor::actorCount);

    Director *dir = Director::getDirector();
    dir->allocate(CamActor::actorCount + ServoActor::actorCount);
    dir->add((Actor **)ServoActor::actors, ServoActor::actorCount);
    dir->add((Actor **)CamActor::actors, CamActor::actorCount);
    display(dir);

    dir->sort();
    printf("\n");
    display(dir);

    printf("\n");
    dir->find("hmirror");
    dir->find("brightness");
    dir->find("move");
    dir->find("special_effect");
    dir->find("angle");
    dir->find("speed");
    int err = dir->find("spud")->act(40);
    printf("err=%d\n", err);
}

void testQuery()
{
    char var[32] = {0};
    const char *qry = "?var=ease&id=1&speed=50&angle=90&val=356";

    esp_err_t err = queryVar(qry, "var", var, sizeof(var));
    int id, speed, angle = 0;
    queryVal(qry, "id", &id);
    queryVal(qry, "speed", &speed);
    queryVal(qry, "angle", &angle);
    printf("%s id=%d speed=%d angle=%d\n", var, id, speed, angle);

    int val = 0;
    err = queryBuf(qry, var, sizeof(var), &val);
    printf("%s val=%d\n", var, val);
}

void testRequest()
{
    httpd_req_t rq;
    httpd_req_t *req = &rq;
    httpd_req_set_url_query_str(req, "?var=ease&index=1&&angle=95&speed=60&type=02");
    size_t len = httpd_req_get_url_query_len(req);
    char buffer[128];
    httpd_req_get_url_query_str(req, buffer, sizeof(buffer));
    printf("len=%lu buffer=%s\n", len, buffer);

    char variable[32];
    queryVar(buffer, "var", variable, sizeof(variable));

    printf("var=%s\n", variable);

    int index, angle, speed, type = 0;
    queryVal(buffer, "index", &index);
    queryVal(buffer, "angle", &angle);
    queryVal(buffer, "speed", &speed);
    queryVal(buffer, "type", &type);
    printf("%s index=%d angle=%d speed=%d type=%d\n",
           variable, index, angle, speed, type);
}

void testControlHandler()
{
    MicroTerm term;
    sensor_t theSensor;
    CamActor::initializeCamActors(&theSensor);
    ServoActor::initializeServoActors(&term);

    printf("camCount: %lu servoCount: %lu\n",
           CamActor::actorCount, ServoActor::actorCount);

    Director *dir = Director::getDirector();
    dir->allocate(CamActor::actorCount + ServoActor::actorCount);
    dir->add((Actor **)ServoActor::actors, ServoActor::actorCount);
    dir->add((Actor **)CamActor::actors, CamActor::actorCount);
    dir->sort();

    httpd_req_t rq;
    httpd_req_t *req = &rq;
    ControlHandler ch;
 
    httpd_req_set_url_query_str(req, "?var=ease&index=1&angle=95&speed=60&type=02");
    esp_err_t err = ch.handle(req);
    printf("err=%d\n", err);
 
    httpd_req_set_url_query_str(req, "?var=framesize&val=8");
    err = ch.handle(req);
    printf("err=%d\n", err);
}

int main(int argc, char **argv)
{
    // testDirector();
    // testQuery();
    // testRequest();
    testControlHandler();
}
#endif // ARDUINO
