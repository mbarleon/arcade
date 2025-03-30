/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** ADisplayModule
*/

#ifndef ADISPLAYMODULE_HPP_
    #define ADISPLAYMODULE_HPP_
    #include "IDisplayModule.hpp"

namespace arcade::display {
    class ADisplayModule : public IDisplayModule {
        public:
            ADisplayModule() = default;
            virtual ~ADisplayModule() = 0;

            void draw(Entities entities) override;
            std::pair<types::Position, types::InputEvent> event() override;

            const std::string &getName() const override;

        protected:
            std::string _name;
    };
};

#endif /* !ADISPLAYMODULE_HPP_ */
