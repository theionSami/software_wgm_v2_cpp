/**
 * @file feedback_management.h
 * @author sami dhiab (sami@theion.de)
 * @brief feedback managment file
 * @version 0.1
 * @date 2022-07-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <iostream>

namespace wgm_feedbacks
{
    /********* enumeration classes ***********/
    enum class enum_proc_feedback
    {
        proc_success = 1,
        proc_error = 0
    };
    enum class enum_sys_feedback
    {
        sys_success = 2,
        sys_error = -1
    };
    enum class enum_hw_feedback
    {
        hw_success = 3,
        hw_error = -2
    };
    /*********** hardware specific implementation *************/
        /************** hardware feedback ************/
    class hw_communication
    {
    public:
        template<typename T> void emit(T response);
        template<typename T> void parse(T data);
    };
    template<typename T> void hw_communication::emit(T response)
    {

    }
    template<typename T> void parse(T data)
    {

    }
    class hw_feedback
    {
    private:
        hw_communication hw_com_handler;
        enum_hw_feedback hw_feedback_value = enum_hw_feedback::hw_success;
    public:
        void report_success();
        void report_error();
        enum_hw_feedback get_feedback();
        bool report_feedback();

    };
    bool hw_feedback::report_feedback()
    {
        if (get_feedback() == enum_hw_feedback::hw_success)
        {
            report_success();
            return true;
        }
        report_error();
        return false;
    }
    enum_hw_feedback hw_feedback::get_feedback()
    {
        return hw_feedback_value;
    }
    void hw_feedback::report_success()
    {
        hw_com_handler.emit(enum_hw_feedback::hw_success);
    }

    void hw_feedback::report_error()
    {
        hw_com_handler.emit(enum_hw_feedback::hw_error);
    }

    /**************** system feedback ***************/
    class sw_communication
    {
    public:
        template<typename T> void emit(T cmd);
        template<typename T> void parse(T data);
    };
    template<typename T> void sw_communication::emit(T cmd)
    {

    }
    template<typename T> void sw_communication::parse(T data)
    {

    }
    class sys_feedback
    {
    private:
        sw_communication sw_com_handler;
        enum_sys_feedback sys_feedback_value;
        hw_feedback low_level_feedback;
    public:
        bool report_success();
        bool report_error();
        enum_sys_feedback get_feedback();
        bool report_feedback();
    };
    bool sys_feedback::report_feedback()
    {
        if (get_feedback() == enum_sys_feedback::sys_success)
        {
            report_success();
            return true;
        }
        report_error();
        return false;
    }
    enum_sys_feedback sys_feedback::get_feedback()
    {
        return sys_feedback_value;
    }
    bool sys_feedback::report_success()
    {
        std::cout << "system reported success" << std::endl;
        sys_feedback_value = enum_sys_feedback::sys_success;
        return true;
    }
    bool sys_feedback::report_error()
    {
        std::cout << "system reported success" << std::endl;
        sys_feedback_value = enum_sys_feedback::sys_success;
        return true;
    }
    /********** processes feedbacks ************/
    class proc_feedback
    {
    private:
        std::string process_name;
        sys_feedback low_level_feedback;
        enum_proc_feedback proc_feedback_value;
    public:
        proc_feedback()=default;
        proc_feedback(std::string& process): process_name(process)
        {
            std::cout << "deleting "<<process_name << std::endl;
        }
        virtual ~proc_feedback()
        {
            std::cout << "deleting "<<process_name << std::endl;
        }
        enum_proc_feedback get_this_process_feedback()
        {
            return proc_feedback_value;
        }
        bool report_success();
        bool report_error();
        template <typename T>
        bool report_feedback(T* process);
    };

    /**
     * @brief report feedback: check lower level and 
     * 
     * @return true 
     * @return false 
     */
    template <typename T>
    bool proc_feedback::report_feedback(T* process)
    {
        if (process->get_sys_feedback() == enum_sys_feedback::sys_success)
        {
            //report_success();
            return true;
        }
        report_error();
        return false;
    }
    bool proc_feedback::report_success()
    {
        std::cout << "process reported success" << std::endl;
        proc_feedback_value = enum_proc_feedback::proc_success;
        return true;
    }
    bool proc_feedback::report_error()
    {
        std::cout << "process reported error" << std::endl;
        proc_feedback_value = enum_proc_feedback::proc_error;
        return false;
    }


}


