#include "Facade/Facade.h"
#include "Logica/Entrenador.h"
#include <dpp/appcommand.h>
#include <dpp/dpp.h>
#include <iostream>

#include "Generador/GeneradorAleatorio.h"
#include "Generador/GeneradorFijo.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
const std::string BOT_TOKEN =
    "MTMxNTI5MzY4MzQxMDY2NTU4Nw.GBhMJP.NEzdh74YaxbqNFW4IT-HI4w_aRetW0lisH4tq4";

int main() {
  // TESTS PARA NO VOLVERME LOCO
  //   Facade::getInstance()->unirBatalla("Hugo");
  //   Facade::getInstance()->unirBatalla("Chorro");
  //   Facade::getInstance()->iniciarBatalla(new GeneradorFijo());
  //   std::cout << Facade::getInstance()->mostrarPokedex() << std::endl;
  //   std::cout << Facade::getInstance()->seleccionarPokemon("Aurorus", "Hugo")
  //             << endl;
  //   std::cout << Facade::getInstance()->seleccionarPokemon("Pikachu",
  //   "Chorro")
  //             << endl;
  //   std::cout << Facade::getInstance()->desplegarMenuAtaque("Hugo") <<
  //   std::endl; std::cout << Facade::getInstance()->atacar("Hugo", "Rayo
  //   Gelido") << endl; std::cout <<
  //   Facade::getInstance()->desplegarMenuAtaque("Chorro")
  //             << std::endl;
  //   std::cout << Facade::getInstance()->atacar("Chorro", "Bola Voltio") <<
  //   endl; std::cout << Facade::getInstance()->desplegarMenuAtaque("Hugo") <<
  //   std::endl; std::cout << Facade::getInstance()->atacar("Hugo", "Placaje")
  //   << endl; Facade::resetInstance();
  //   Facade::getInstance()->unirBatalla("Hugo");
  //   Facade::getInstance()->unirBatalla("Chorro");
  // }

  dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

  bot.on_log(dpp::utility::cout_logger());

  // COMANDO UNIR EN BATALLA
  bot.on_slashcommand([](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "unirme") {
      // Obtener el nombre de usuario que ejecutó el comando
      std::string nombreUsuario = event.command.usr.username;

      // Llamar a la función unirBatalla con el nombre de usuario
      std::string respuesta = Facade::getInstance()->unirBatalla(nombreUsuario);
      event.reply(respuesta);
    }
  });

  // POKEDEX
  bot.on_slashcommand([](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "pokedex") {

      // imprime pokedex por pantalla
      std::string respuesta = Facade::getInstance()->mostrarPokedex();
      event.reply(respuesta);
    }
  });

  // COMANDO INICIAR BATALLA
  bot.on_slashcommand([](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "batalla") {

      std::string respuesta =
          Facade::getInstance()->iniciarBatalla(new GeneradorAleatorio());
      event.reply(respuesta);
    }
  });

  // COMANDO MENU ATAQUE
  bot.on_slashcommand([](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "menu_ataque") {
      std::string nombreUsuario = event.command.usr.username;

      std::string respuesta =
          Facade::getInstance()->desplegarMenuAtaque(nombreUsuario);
      event.reply(respuesta);
    }
  });

  // COMANDO SELECCIONAR Pokemon
  bot.on_slashcommand([&bot](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "llamar") {
      try {
        std::string nombreUsuario = event.command.usr.username;
        std::string pokemonNombre =
            std::get<std::string>(event.get_parameter("nombre"));
        event.reply(Facade::getInstance()->seleccionarPokemon(pokemonNombre,
                                                              nombreUsuario));
      } catch (const std::bad_variant_access &e) {
        event.reply(
            "Error: El parámetro proporcionado no es un string válido.");
      }
    }
  });
  ;

  // ATACAR
  bot.on_slashcommand([&bot](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "atacar") {
      try {
        std::string nombreUsuario = event.command.usr.username;
        std::string nombreMov =
            std::get<std::string>(event.get_parameter("ataque"));
        event.reply(Facade::getInstance()->atacar(nombreUsuario, nombreMov));
      } catch (const std::bad_variant_access &e) {
        event.reply(
            "Error: El parámetro proporcionado no es un string válido.");
      }
    }
  });
  ;

  // CAMBIAR POKEMON
  bot.on_slashcommand([&bot](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "cambio") {
      try {
        std::string nombreUsuario = event.command.usr.username;
        std::string nombrePok =
            std::get<std::string>(event.get_parameter("pokemon"));
        event.reply(
            Facade::getInstance()->cambiarPokemon(nombrePok, nombreUsuario));
      } catch (const std::bad_variant_access &e) {
        event.reply(
            "Error: El parámetro proporcionado no es un string válido.");
      }
    }
  });
  ;

  // COMANDO FINALIZAR BATALLA | **EXPERIMENTAL**
  bot.on_slashcommand([](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "finalizar") {

      Facade::resetInstance();
      event.reply("Entorno reiniciado:exclamation:\n");
    }
  });

  bot.on_ready([&bot](const dpp::ready_t &event) {
    if (dpp::run_once<struct register_bot_commands>()) {

      // Comando 1: unirme
      dpp::slashcommand unirme("unirme", "Unirse a la lista de espera",
                               bot.me.id);

      // Comando 2: llamar con un parámetro "nombre"
      dpp::slashcommand llamar("llamar", "Selecciona un Pokémon", bot.me.id);
      llamar.add_option(
          dpp::command_option(dpp::co_string, "nombre", "Nombre del Pokémon",
                              true) // Parámetro obligatorio
      );

      dpp::slashcommand batalla("batalla", "Inicia la batalla!", bot.me.id);

      dpp::slashcommand pokedex("pokedex", "Desplegar pokemones disponibles",
                                bot.me.id);

      dpp::slashcommand menu_ataque("menu_ataque",
                                    "Desplegar el menú de ataque!", bot.me.id);

      dpp::slashcommand atacar("atacar", "Ejecuta un ataque", bot.me.id);
      atacar.add_option(
          dpp::command_option(dpp::co_string, "ataque", "Nombre del ataque",
                              true) // Parámetro obligatorio
      );

      dpp::slashcommand cambio("cambio", "Cambia tu pokemon activo", bot.me.id);
      cambio.add_option(
          dpp::command_option(dpp::co_string, "pokemon", "Nombre del pokemon",
                              true) // Parámetro obligatorio
      );

      dpp::slashcommand finalizar(
          "finalizar", "Reinicia el entorno para iniciar una nueva batalla",
          bot.me.id);

      // Crear un vector de comandos
      std::vector<dpp::slashcommand> comandos = {unirme,  llamar,      batalla,
                                                 pokedex, menu_ataque, atacar,
                                                 cambio,  finalizar};

      // Registrar todos los comandos
      for (auto &comando : comandos) {
        bot.global_command_create(
            comando, [](const dpp::confirmation_callback_t &callback) {
              if (callback.is_error()) {
                std::cerr << "Error al registrar comando: "
                          << callback.get_error().message << std::endl;
              } else {
                std::cout << "Comando registrado exitosamente: "
                          << callback.get<dpp::slashcommand>().name
                          << std::endl;
              }
            });
      }
    }
  });
  bot.start(dpp::st_wait);
}
