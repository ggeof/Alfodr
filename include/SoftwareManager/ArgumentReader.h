#ifndef __ARGUMENTREADER_H__
#define __ARGUMENTREADER_H__

#include <exception>
#include <string>
#include <vector>

namespace Alfodr {
    namespace SoftwareManager{
        
        struct Argument
        {
            const char * name;              // --Name
            const char * shortName = "";    // -shortname
            const char * helper = "";       // Text showed if the helper is called

            const char * value = nullptr;   // Value of argument, if no value is expecting, the value is "" if the argument is present
            bool noValue = false;           // Expect no value 
        };
        

        class ArgumentReader
        {
        public:


            /**
             * @brief Exception quand la modification d'un paramètre à échoué
             * 
             */
            class ArgumentNotRecognized : public std::exception
            {
                public:
                    ArgumentNotRecognized(const char* _arg) : std::exception(), argument(_arg) {};

                    virtual const char* what() const throw() { return (std::string(argument)+" is not a valid argument :").c_str(); }

                private:
                    const char* argument;
            };

            /**
             * @brief Exception quand la modification d'un paramètre à échoué
             * 
             */
            class MissingValueForArgument : public std::exception
            {
                public:
                    MissingValueForArgument(const char* _arg) : std::exception(), argument(_arg) {};

                    virtual const char* what() const throw() { return (std::string(argument)+" must be have a value !").c_str(); }

                private:
                    const char* argument;
            };

            /**
             * @brief Construct a new Argument Reader object
             * 
             */
            ArgumentReader();

            /**
             * @brief Destroy the Argument Reader object
             * 
             */
            ~ArgumentReader();

            /**
             * @brief Add a argument in the list of argument
             * 
             * @param arg New argument added
             */
            void addArgument(Argument arg);
            /**
             * @brief Add a list argument in the list of argument
             * 
             * @param args List of argument must be added
             */
            void addArgument(std::vector<Argument> args);

            /**
             * @brief Get the Arguments object
             * 
             * @return std::vector<Argument> Tout les arguments attendus
             */
            std::vector<Argument> getArguments() const { return this->arguments; }

            /**
             * @brief Read the arguments of a program
             * 
             * @param argc Number of arguments
             * @param arg Arguments present
             * @return std::vector<Argument> List of argument present
             */
            std::vector<Argument> readArgument(int argc, char * arg[]);

            /**
             * @brief Show the helper
             * 
             */
            void showHelper() const;

        protected:
            /**
             * @brief Argument acceptable by the program
             * 
             */
            std::vector<Argument> arguments;
        };
        
        
        
    }
}
#endif // __ARGUMENTREADER_H__