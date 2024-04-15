#include "Timer.h"

namespace std {
    template <>
    struct hash<TIMER_KEY> {
        size_t operator()(const TIMER_KEY& k) const {
            return hash<std::string>()(k.first) ^ (hash<std::string>()(k.second) << 1);
        }
    };
}

std::unordered_map<TIMER_KEY, TIMER_VALUE> Timer::timer{};
std::unordered_map<TIMER_KEY, bool> Timer::is_timing{};
std::unordered_map<TIMER_KEY, double> Timer::single_timer{};

void Timer::show_single_tick_info(std::string classname, std::string funcname, TIMER_VALUE timer_val) {
    std::cout << "Call " << classname << "." << funcname
                << " for the " << timer_val.first << " time, time consumption: "
                << timer_val.second << "s." << std::endl;
}

void Timer::tick(std::string classname, std::string funcname) {
#ifdef __MPI
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    TIMER_KEY key = std::make_pair(classname, funcname);

    if (!is_timing[key]) {
        is_timing[key] = true;
        single_timer[key] = MPI_Wtime();
    } else {
        is_timing[key] = false;
        double endTime = MPI_Wtime();
        double duration = endTime - single_timer[key];
        timer[key].second += duration;
        timer[key].first++;
        if (rank == 0) {
            show_single_tick_info(classname, funcname, timer[key]);
        }
    }
#else
    TIMER_KEY key = std::make_pair(classname, funcname);
    if (!is_timing[key]) {
        is_timing[key] = true;
        auto current_time = std::chrono::steady_clock::now();
        auto duration = current_time.time_since_epoch();
        single_timer[key] = std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
    } else {
        is_timing[key] = false;
        auto endTime = std::chrono::steady_clock::now();
        auto duration = endTime.time_since_epoch();
        timer[key].second += duration.count() / 1000.0f;
        timer[key].first ++;
        show_single_tick_info(classname, funcname, timer[key]);
    }
#endif
}

void Timer::show_info() {
    std::cout << std::setw(20) << "CLASS NAME" << std::setw(40) << "FUNCTION" << std::setw(20) << "CALLS" << std::setw(30) << "TIME (s)" << std::endl;
    for (const auto& entry : timer) {
        const TIMER_KEY& key = entry.first;
        const TIMER_VALUE& value = entry.second;
        std::cout << std::setw(20) << key.first 
                  << std::setw(40) << key.second 
                  << std::setw(20) << value.first 
                  << std::setw(30) << std::scientific 
                  << std::setprecision(7) << value.second << std::endl;
    }
}
