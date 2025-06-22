#include "Fecha.h"
#include <iostream>
#include <ctime>

Fecha::Fecha()
{
    // Constructor por defecto
}

Fecha::~Fecha()
{
    // Destructor
}

Anio Fecha::getAnio() const
{
    return anio;
}

void Fecha::setAnio(Anio newAnio)
{
    anio = newAnio;
}

int Fecha::getMes() const
{
    return mes;
}

void Fecha::setMes(int newMes)
{
    mes = newMes;
}

int Fecha::getDia() const
{
    return dia;
}

void Fecha::setDia(int newDia)
{
    dia = newDia;
}

bool Fecha::esFinDeSemana() const
{
    struct tm timeStruct = {};
    timeStruct.tm_year = anio.getAnio() - 1900;
    timeStruct.tm_mon = mes - 1;
    timeStruct.tm_mday = dia;
    mktime(&timeStruct);
    return (timeStruct.tm_wday == 0 || timeStruct.tm_wday == 6); // Domingo o Sábado
}

/*bool Fecha::esFeriadoEcuador() const {
    Fecha carnaval = calcularCarnaval(anio.getAnio());
    Fecha segundoDiaCarnaval = carnaval;
    segundoDiaCarnaval.dia++;
    Fecha viernesSanto = calcularViernesSanto(anio.getAnio());

    if ((mes == 1 && dia == 1) ||
        (mes == 5 && dia == 1) ||
        (mes == 5 && dia == 24) ||
        (mes == 8 && dia == 10) ||
        (mes == 10 && dia == 9) ||
        (mes == 11 && dia == 2) ||
        (mes == 11 && dia == 3) ||
        (mes == 12 && dia == 25)) {
        return true;
    }

    if ((mes == carnaval.getMes() && dia == carnaval.getDia()) ||
        (mes == segundoDiaCarnaval.getMes() && dia == segundoDiaCarnaval.getDia()) ||
        (mes == viernesSanto.getMes() && dia == viernesSanto.getDia())) {
        return true;
    }

    return false;
}*/

bool Fecha::esFeriadoEcuador() const
{
    struct Feriado
    {
        int dia;
        int mes;
        bool trasladable;
    };

    Feriado feriados[] = {
        {1, 1, false},   // Año Nuevo
        {1, 5, true},    // Día del Trabajo
        {25, 12, false}, // Navidad
        {24, 5, true},   // Batalla de Pichincha
        {10, 8, true},   // Primer Grito de Independencia
        {9, 10, true},   // Independencia de Guayaquil
        {2, 11, true},   // Día de los Difuntos
        {3, 11, true}    // Independencia de Cuenca
    };

    struct tm fechaActual = {};
    fechaActual.tm_year = anio.getAnio() - 1900;
    fechaActual.tm_mon = mes - 1;
    fechaActual.tm_mday = dia;
    mktime(&fechaActual);

    // Verificar feriados fijos
    for (const auto &feriado : feriados)
    {
        struct tm f = {};
        f.tm_year = anio.getAnio() - 1900;
        f.tm_mon = feriado.mes - 1;
        f.tm_mday = feriado.dia;
        mktime(&f);

        if (!feriado.trasladable)
        {
            // Comparar con fecha exacta
            if (f.tm_mday == fechaActual.tm_mday &&
                f.tm_mon == fechaActual.tm_mon &&
                f.tm_year == fechaActual.tm_year)
            {
                return true;
            }
        }
        else
        {
            // Aplicar traslado si aplica
            switch (f.tm_wday)
            {
            case 0:
                f.tm_mday += 1;
                break; // Domingo → lunes
            case 2:
                f.tm_mday -= 1;
                break; // Martes → lunes anterior
            case 3:
            case 4:
                f.tm_mday += (5 - f.tm_wday);
                break; // Miércoles/Jueves → viernes
            case 6:
                f.tm_mday -= 1;
                break; // Sábado → viernes
            }
            mktime(&f);

            if (f.tm_mday == fechaActual.tm_mday &&
                f.tm_mon == fechaActual.tm_mon &&
                f.tm_year == fechaActual.tm_year)
            {
                return true;
            }
        }
    }

    // Verificar feriados móviles: Carnaval y Viernes Santo
    Fecha carnaval = calcularCarnaval(anio.getAnio());
    /*Fecha martesCarnaval = carnaval;
    martesCarnaval.dia += 1;*/
    Fecha martesCarnaval = carnaval;
    int diasMes[12] = {31, 28, 31, 30, 31, 30,
                       31, 31, 30, 31, 30, 31};

    int anioCarnaval = carnaval.getAnio().getAnio();
    if ((anioCarnaval % 4 == 0 && anioCarnaval % 100 != 0) || (anioCarnaval % 400 == 0))
    {
        diasMes[1] = 29;
    }

    martesCarnaval.setDia(martesCarnaval.getDia() + 1);
    if (martesCarnaval.getDia() > diasMes[carnaval.getMes() - 1])
    {
        martesCarnaval.setDia(1);
        martesCarnaval.setMes(carnaval.getMes() + 1);
        if (martesCarnaval.getMes() > 12)
        {
            martesCarnaval.setMes(1);
            Anio nuevoAnio;
            nuevoAnio.setAnio(anioCarnaval + 1);
            martesCarnaval.setAnio(nuevoAnio);
        }
    }

    Fecha viernesSanto = calcularViernesSanto(anio.getAnio());

    // Comparar fechas móviles
    if ((dia == carnaval.getDia() && mes == carnaval.getMes()) ||
        (dia == martesCarnaval.getDia() && mes == martesCarnaval.getMes()) ||
        (dia == viernesSanto.getDia() && mes == viernesSanto.getMes()))
    {
        return true;
    }

    return false;
}

void Fecha::ajustarFechaPago() {
    struct tm timeStruct = {};
    timeStruct.tm_year = anio.getAnio() - 1900;
    timeStruct.tm_mon = mes - 1;
    timeStruct.tm_mday = dia;

    mktime(&timeStruct);  // Inicializa correctamente la estructura

    int diaOriginal = dia;
    int mesOriginal = mes;
    int anioOriginal = anio.getAnio();

    bool fueAjustada = false;
    int contador = 0;  // Seguridad contra bucles infinitos

    while (true) {
        // Actualizar la fecha temporal con la estructura actual
        Fecha fechaTemporal;
        Anio aTemp;
        aTemp.setAnio(timeStruct.tm_year + 1900);
        fechaTemporal.setAnio(aTemp);
        fechaTemporal.setMes(timeStruct.tm_mon + 1);
        fechaTemporal.setDia(timeStruct.tm_mday);

        if (!fechaTemporal.esFeriadoEcuador() && !fechaTemporal.esFinDeSemana()) {
            // Si la fecha es válida, salimos
            break;
        }

        fueAjustada = true;

        /*std::cout << "Reajustando desde: "
                  << fechaTemporal.getDia() << "/"
                  << fechaTemporal.getMes() << "/"
                  << fechaTemporal.getAnio().getAnio() << std::endl;*/

        // Avanzamos un día (para garantizar que siempre progresamos)
        timeStruct.tm_mday += 1;
        mktime(&timeStruct);  // Recalcula correctamente día/mes/año/semana

        // Seguridad: si después de 100 iteraciones no se resuelve, salimos
        if (++contador > 100) {
            std::cerr << "Error: bucle infinito al ajustar la fecha de pago.\n";
            break;
        }
    }

    // Guardamos la nueva fecha
    dia = timeStruct.tm_mday;
    mes = timeStruct.tm_mon + 1;
    anio.setAnio(timeStruct.tm_year + 1900);

    if (fueAjustada) {
        std::cout << "Fecha de pago original: "
                  << diaOriginal << "/" << mesOriginal << "/" << anioOriginal << std::endl;
        std::cout << "Fecha de pago ajustada: "
                  << dia << "/" << mes << "/" << anio.getAnio() << std::endl;
    } else {
        std::cout << "La fecha " << dia << "/" << mes << "/" << anio.getAnio()
                  << " no requiere ajustes (no es feriado ni fin de semana)." << std::endl;
    }
}




/*void Fecha::ajustarFechaPago() {
    struct tm timeStruct = {};
    timeStruct.tm_year = anio.getAnio() - 1900;
    timeStruct.tm_mon = mes - 1;
    timeStruct.tm_mday = dia;
    mktime(&timeStruct);

    if (esFeriadoEcuador()) {
        if (timeStruct.tm_wday == 2) {
            timeStruct.tm_mday -= 1;
        } else if (timeStruct.tm_wday == 4) {
            timeStruct.tm_mday += 1;
        } else if (timeStruct.tm_wday == 3) {
            if (dia - 2 > 0) {
                timeStruct.tm_mday -= 2;
            } else {
                timeStruct.tm_mday += 2;
            }
        } else if (timeStruct.tm_wday == 5) {
            timeStruct.tm_mday -= 1;
        }

        mktime(&timeStruct);
        dia = timeStruct.tm_mday;
        mes = timeStruct.tm_mon + 1;
        anio.setAnio(timeStruct.tm_year + 1900);

        if (esFeriadoEcuador()) {
            ajustarFechaPago();
        }
    }

    while (esFinDeSemana()) {
        timeStruct.tm_mday += 1;
        mktime(&timeStruct);
        dia = timeStruct.tm_mday;
        mes = timeStruct.tm_mon + 1;
        anio.setAnio(timeStruct.tm_year + 1900);
    }
}*/

Fecha Fecha::calcularCarnaval(int anio) const
{
    Fecha pascua = calcularViernesSanto(anio);
    pascua.dia += 2;

    int diasPorMes[12] = {31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31};

    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
    {
        diasPorMes[1] = 29;
    }

    int diasARestar = 48;
    while (diasARestar > 0)
    {
        pascua.dia--;
        if (pascua.dia == 0)
        {
            pascua.mes--;
            if (pascua.mes == 0)
            {
                pascua.mes = 12;
                anio--;
                pascua.anio.setAnio(anio);
                diasPorMes[1] = ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) ? 29 : 28;
            }
            pascua.dia = diasPorMes[pascua.mes - 1];
        }
        diasARestar--;
    }

    return pascua;
}

Fecha Fecha::calcularViernesSanto(int anio) const
{
    int a = anio % 19;
    int b = anio / 100;
    int c = anio % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
    int mes = (h + l - 7 * m + 114) / 31;
    int dia = ((h + l - 7 * m + 114) % 31) + 1;

    Fecha viernesSanto;
    Anio aObj;
    aObj.setAnio(anio);
    viernesSanto.setAnio(aObj);
    viernesSanto.setMes(mes);
    viernesSanto.setDia(dia - 2);
    return viernesSanto;
}

void Fecha::mostrarFecha() const
{
    std::cout << dia << "/" << mes << "/" << anio.getAnio() << std::endl;
}
