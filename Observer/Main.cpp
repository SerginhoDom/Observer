#include <iostream>
#include <list>

class ISubject;

class IObserver {
public:
    virtual void update() = NULL;

protected:
    std::list<ISubject*> subs;
    friend ISubject;
};

class ISubject {
public:
    void attech(IObserver* obs) {
        data = obs;
        data->subs.push_back(this);
        pos = data->subs.end();
        pos--;
    }

    void detach() {
        data->subs.erase(pos);
        data = nullptr;
    }

    virtual void notify(float) = NULL;
private:
    IObserver* data;
    std::list<ISubject*>::iterator pos;
};

class WeatherData : public IObserver {
public:
    void setTemp(float _val) {
        temp = _val;
        update();
    }

    void update() override {
        for (auto iter : subs)
            iter->notify(temp);
    }
private:
    float temp = 0;
};

class FirstUI : public ISubject{
public:
    void notify(float _Val) override {
        last_val = _Val;
        std::cout << last_val << std::endl;
    }

private:
    float last_val;
};

int main() {
    WeatherData obj;
    obj.setTemp(1);
    FirstUI subj1, subj2, subj3;
    subj1.attech(&obj);
    subj2.attech(&obj);
    subj3.attech(&obj);
    obj.setTemp(20);
    subj1.detach();
    obj.setTemp(10);
}