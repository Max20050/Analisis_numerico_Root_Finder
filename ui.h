#pragma once
#pragma once
#include <iostream>
#include <exception>

namespace UiMenu
{
    class FueraDeRango :public std::exception
    {
    public:
        std::string message;
        FueraDeRango(std::string message) { this->message = message; };
        const char* what() const throw() {
            return message.c_str();
        }
    };

    class NoImplementado :public std::exception
    {
    public:
        std::string message;
        NoImplementado(std::string message) { this->message = message; };
        const char* what() const throw() {
            return message.c_str();
        }
    };

    struct Menu
    {
        int id;
        std::string text;
    };

    int selection(Menu menu[], int n) {
        int opcion;
        try
        {
            std::cout << "ingrese una opcion" << std::endl;
            std::cin >> opcion;
            if (opcion < 0 || opcion > n)
            {
                throw (FueraDeRango("La opcion ingresada no esta en la lista, por favor vuelva a ingresar"));
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return selection(menu, n);
        }
        return opcion;
    }

    void MostrarMenu(int n, Menu menu[]) {
        for (int i = 0; i < n; i++)
        {
            std::cout << menu[i].id << " " << menu[i].text << std::endl;
        }
    }


} // namespace UiMenu

// Crear Menu item:
/*
    UiMenu::Menu menu_name[n] {
        {1,"option1_text"},
                 .
                 .
                 .
        {n,"optio_n_text"}
    }
*/

// Mostrar el menu en la consola
/*
    UiMenu::MostrarMenu(n,menu_name);
*/

// Sleccionar una opcion valida
/*
    int variable_opcion = UiMenu::selection(menu_name,n);
*/