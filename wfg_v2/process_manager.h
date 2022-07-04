/**
 * @file process_manager.h
 * @author sami dhiab (sami@theion.de)
 * @brief process management package
 * @version 0.1
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <vector>
#include "heating_system.h"
#include "cnt_alignment_system.h"

namespace wgm_processes
{
    /************* interface process management **********/
    /**
     * @brief interface process managemnt for user
     * do not modify!
     */
    class Iprocesses_managment
    {
    public:
        Iprocesses_managment() {
        }
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual void stop_all() {};
        virtual void start_all() {};
        virtual ~Iprocesses_managment() {
        }
    };
    /************* processes interface and implementation**********/
    /**
     * @brief add system processes as following:
     * create interface and inherit from Iprocesses_managment.
     * create abstract methods start_process and stop_process
     * create the implementation class, redefine these methods
     * create the actual process system inside constructor
     * delete it in the destructor (virtual)
     */
     /****************** interface heating process *****************/
    class Iheating_process : public Iprocesses_managment
    {
    public:
        Iheating_process()
        {
            std::cout << "creating heating process " << std::endl;
        }

        virtual ~Iheating_process()
        {
        }
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
    };
    /************* implementation heating process ************/
    class heating_process : public Iheating_process
    {
    public:
        sulfur_heating_system::Isulfur_heating_controller* heating_sys;
        heating_process() {
            heating_sys = new sulfur_heating_system::sulfur_heating_controller();
        }
        virtual void start_process();
        virtual void stop_process();
        virtual ~heating_process()
        {
            std::cout << "deleting heating process " << std::endl;
            delete heating_sys;
        }
    };
    void heating_process::start_process()
    {
        heating_sys->turn_on_heating();
    }
    void heating_process::stop_process()
    {
        heating_sys->turn_off_heating();
    }
    /****************** interface cnt alignment *******************/
    class Ialigning_process : public Iprocesses_managment
    {
    public:
        Ialigning_process()
        {
            std::cout << "creating aligning process " << std::endl;
        }
        virtual ~Ialigning_process()
        {
        }
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
    };

    /******************* implementation cnt alignment ***************/
    class aligning_process : public Ialigning_process
    {
    private:
        cnt_alignment_system::Icnt_aligning_controller* aligning_sys;
    public:
        aligning_process() {
            aligning_sys = new cnt_alignment_system::cnt_aligning_controller();
        }
        virtual void start_process();
        virtual void stop_process();
        virtual ~aligning_process()
        {
            std::cout << "deleting aligning process " << std::endl;
            delete aligning_sys;
        }
    };
    void aligning_process::start_process()
    {
        aligning_sys->start_aligning();
    }
    void aligning_process::stop_process()
    {
        aligning_sys->stop_aligning();
    }









    /******************** implementation process management ************/
    /**
     * @brief implementation process managemnt
     * add new process inside constructor
     * later will be possible to add new processes from interface method
     * add and delete from delete method
     */
    class process_management : public Iprocesses_managment
    {
    private:
        std::vector<Iprocesses_managment*> processesvector;
    public:
        process_management() {
            std::cout << "creating process manager" << std::endl;
            /***** add new process *******/
            /***** add heating process ***/
            Iheating_process* h_proc = new heating_process();
            processesvector.push_back(h_proc);
            std::cout << "added heating process to process vector" << std::endl;
            /***** add aligning process ***/
            Ialigning_process* a_proc = new aligning_process();
            processesvector.push_back(a_proc);
            std::cout << "added aligning process to process vector" << std::endl;
            /***** add insertion process ***/

        
        
        
        }
        // clean up destruction
        virtual ~process_management() {
            std::cout << "deleting process manager" << std::endl;
            for (auto process : processesvector)
            {
                if (process != nullptr)
                {
                    delete process;
                }
                else
                {
                    std::cout << "can't free memory" << std::endl;
                    break;
                }
            }
        }
        virtual void start_process();
        virtual void stop_process();
        virtual void start_all();
        virtual void stop_all();
        virtual void add_process();
        virtual void delete_process();
    };
    void process_management::start_process()
    {
        std::cout << "process started" << std::endl;
    }
    void process_management::stop_process()
    {
        std::cout << "process stopped" << std::endl;
    }
    void process_management::start_all()
    {
        std::cout << "executing all processes" << std::endl;
        for (auto process : processesvector)
        {
            if (process != nullptr)
            {
                process->start_process();
            }
            else std::cout << "empty vector" << std::endl;
        }
    }
    void process_management::stop_all()
    {
        std::cout << "stopping all processes" << std::endl;

        for (auto process : processesvector)
        {
            if (process != nullptr)
            {
                process->stop_process();
            }
            else std::cout << "empty vector" << std::endl;
        }
    }
    void process_management::add_process()
    {

    }
    void process_management::delete_process()
    {

    }

}

/****************** user code ********************/
class user {
private:
    wgm_processes::Iprocesses_managment* processInterfaces;

public:
    user()
    {
        std::cout << "user started app" << std::endl;

        processInterfaces = new wgm_processes::process_management();
    }
    void run_app()
    {
        processInterfaces->start_all();
    }
    void stop_app()
    {
        processInterfaces->stop_all();
    }
    ~user()
    {
        std::cout << "user stopped app" << std::endl;
        delete processInterfaces;
    }
};

