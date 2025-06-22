#ifndef ANIO_H
#define ANIO_H

class Anio {
private:
    bool anioBisiesto;
    int anio;

public:
    Anio(); // Constructor
    ~Anio(); // Destructor

    bool getAnioBisiesto() const;
    void setAnioBisiesto(bool value);

    int getAnio() const;
    void setAnio(int newAnio);
    //bool validarAnio(int anio);
};

#endif
