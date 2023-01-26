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

#include "process_manager.h"


namespace wgm_processes
{
 
     /****************** interface heating process *****************/
    class Iheating_process : public Iprocesses_managment
    {
    public:
        Iheating_process();
        virtual ~Iheating_process();
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
        virtual long long get_elapsed_time()=0;
        virtual sulfur_heating_system::Isulfur_heating_controller* get_sys_ptr() = 0;

    };
    /************* implementation heating process ************/
    class heating_process : public Iheating_process
    {
    private:
        sulfur_heating_system::Isulfur_heating_controller* heating_sys;
        wgm_monitoring::Itime_monitor* process_timer;
        wgm_monitoring::Iheat_monitor* process_temp_monitor;
        wgm_feedbacks::proc_feedback process_feedback;
        std::string process_name = "heating process";
    public:
        heating_process();
        virtual ~heating_process();
         void start_process() override;
         void stop_process() override;
         std::string get_name() override;
         bool is_proc_success() override;
         long long get_elapsed_time() override;
         sulfur_heating_system::Isulfur_heating_controller* get_sys_ptr() override;

    };
    

}


