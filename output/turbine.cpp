#include <iostream>
#include <ctime>
#include <algorithm>
#include <cassert>

// RPMSensor class definition
class RPMSensor {
public:
     static const float MINRPM;
    static const float MAXRPM;
    float rpmReading;
    bool sensorStatus;
    time_t lastUpdateTime;

    RPMSensor() : rpmReading(0), sensorStatus(true) {}

    void measureRPM(float newRPM) {
        rpmReading = newRPM;
        lastUpdateTime = time(nullptr);
         //pre condition
        assert((inRange(rpmReading) ));
    }

    void checkSensorStatus() {
        // Simulate sensor status check (always operational in this simulation)
        sensorStatus = true;
         //pre condition
        assert(sensorStatus != false );
    }

    bool inRange(double val) {

        return (MINRPM<= val && val<= MAXRPM);

        }

     bool invariant() {
        // Check the invariant condition 
        return inRange(rpmReading);
    }
};
const float RPMSensor::MINRPM = 0;
const float RPMSensor::MAXRPM = 3000;

// ValvePositionSensor class definition
class ValvePositionSensor {
public:
    static const float MIN;
    static const float MAX;
    float valvePosition;
    bool sensorStatus;
    time_t lastUpdateTime;

    ValvePositionSensor() : valvePosition(0.15f), sensorStatus(true) {} // Start with valve position 15%

    void measureValvePosition(float newPosition) {
        valvePosition = newPosition;
        lastUpdateTime = time(nullptr);
        //pre condition
        assert((inRange(valvePosition) ));
    }

    void checkSensorStatus() {
        // Simulate sensor status check (always operational in this simulation)
        sensorStatus = true;
        //pre condition
        assert(sensorStatus != false );

    }

    bool inRange(double val) {

        return (MIN<= val && val<= MAX);

        }

     bool invariant() {
        // Check the invariant condition 
        return inRange(valvePosition);
    }
};
const float ValvePositionSensor::MIN = 0.0f;
const float ValvePositionSensor::MAX = 100.0f;



// TurbineSpeedControlSystem class definition
class TurbineSpeedControlSystem {
public:
    static const float targetRPM;     // declaring static const Target RPM means they are shared across all instances of this class and their values are constant
    static const float tolerance;     // static const Tolerance
    static const float minValvePosition;  // Minimum valve position
    static const float maxValvePosition;  // Maximum valve position

    float currentRPM;
    float valvePosition;
    bool rpmSensorStatus;
    bool valvePositionSensorStatus;

    RPMSensor rpmSensor;
    ValvePositionSensor valveSensor;

    TurbineSpeedControlSystem(): currentRPM(0), valvePosition(0.15f) {}

    void adjustValvePosition(float newPosition) {
        // Precondition check: newPosition should be in range and valvePosition should not be zero
        assert(inRangeValve(newPosition) && valvePosition != 0.0f);
        // Constrain valve position between 10% and 100%
        valvePosition = std::max(0.1f, std::min(newPosition, 1.0f));
        valveSensor.measureValvePosition(valvePosition);
    }

    void compareRPM() {
        currentRPM = rpmSensor.rpmReading;
        float adjustment = (targetRPM - currentRPM) / targetRPM * 0.01; //smaller fluctuation
        adjustValvePosition(valvePosition + adjustment);
        //Pre condition check
        assert((currentRPM < targetRPM || currentRPM > targetRPM) && currentRPM != 0 && targetRPM != 0);
    }


    void updateSensorStatus() {
        rpmSensor.checkSensorStatus();
        valveSensor.checkSensorStatus();
        rpmSensorStatus = rpmSensor.sensorStatus;
        valvePositionSensorStatus = valveSensor.sensorStatus;
        
        //Pre condition
        assert(rpmSensor.sensorStatus == true && valveSensor.sensorStatus == true); //(This is showing error)
    }

    bool isSystemOperational() {
        return rpmSensorStatus && valvePositionSensorStatus;
    }

    bool inRangeRPM(float val) {
        // Check if RPM is within the range
        return (tolerance <= val && val <= targetRPM);
    }

    bool inRangeValve(float val) {
        // Check if valve position is within the range
        return (minValvePosition <= val && val <= maxValvePosition);
    }

    bool invariant() {
        // Check the invariant condition for currentRPM and valvePosition
        return inRangeRPM(currentRPM) && inRangeValve(valvePosition);
    }

    // Getter methods for tester class
    float getCurrentRPM() const {
        return currentRPM;
    }

    float getValvePosition() const {
        return valvePosition;
    }

    bool getRPMSensorStatus() const {
        return rpmSensor.sensorStatus;
    }

    bool getValvePositionSensorStatus() const {
        return valveSensor.sensorStatus;
    }

    bool isSystemOperational() const {
        return rpmSensorStatus && valvePositionSensorStatus;
    }

};

// Initialize static constants outside the class
const float TurbineSpeedControlSystem::targetRPM = 3000.0f;
const float TurbineSpeedControlSystem::tolerance = 0.0f;
const float TurbineSpeedControlSystem::minValvePosition = 0.1f;
const float TurbineSpeedControlSystem::maxValvePosition = 1.0f;

class TurbineSpeedControlSystemTester {
public:
    static void runTests() {
        TurbineSpeedControlSystem controlSystem;

        char choice;
        try {
            do {
                displayMenu();
                std::cin >> choice;

                switch (choice) {
                    case '1':
                        simulateSystemOperation(controlSystem);
                        break;
                    case '2':
                        displaySensorStatus(controlSystem);
                        break;
                    case '3':
                        adjustValvePosition(controlSystem);
                        break;
                    case '4':
                        displayCurrentRPM(controlSystem);
                        break;
                    case '5':
                        displayValvePosition(controlSystem);
                        break;
                    case '6':
                        displaySystemStatus(controlSystem);
                        break;
                    case '7':
                        break;
                    default:
                        std::cout << "Invalid choice. Please enter a number between 1 and 7.\n";
                }
            } while (choice != '7');
        } catch (const std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
    }

private:
    static void displayMenu() {
        std::cout <<"             **************************************";
        std::cout << "\n\t\tTurbineSpeedControlSystem Tester\n"
                  << "1. Simulate System Operation\n"
                  << "2. Display Sensor Status\n"
                  << "3. Adjust Valve Position\n"
                  << "4. Display Current RPM\n"
                  << "5. Display Valve Position\n"
                  << "6. Display System Operational Status\n"
                  << "7. Quit\n"
                  << "Enter choice (1-7): ";
    }

    static void simulateSystemOperation(TurbineSpeedControlSystem& controlSystem) {
    try {
        for (int i = 0; i < 180; i++) {
            float rpmIncrease = std::min(50.0f, (TurbineSpeedControlSystem::targetRPM - controlSystem.rpmSensor.rpmReading) * 0.05f);
            float simulatedRPM = controlSystem.rpmSensor.rpmReading + rpmIncrease;
            controlSystem.rpmSensor.measureRPM(simulatedRPM);
            controlSystem.updateSensorStatus();

            if (controlSystem.isSystemOperational()) {
                controlSystem.compareRPM();

                std::cout << "System is operational. Time: " << i << "s, "
                          << "Current RPM: " << controlSystem.getCurrentRPM() << ", "
                          << "Valve Position: " << controlSystem.getValvePosition() * 100 << "%"
                          << std::endl;
            } else {
                std::cout << "Sensor failure detected. System is not operational." << std::endl;
                break;  // Exit simulation if a sensor failure occurs
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught during system operation: " << e.what() << std::endl;
    }
}

    static void displaySensorStatus(const TurbineSpeedControlSystem& controlSystem) {
        std::cout << "RPM Sensor Status: " << (controlSystem.getRPMSensorStatus() ? "Operational" : "Not Operational") << std::endl;
        std::cout << "Valve Position Sensor Status: " << (controlSystem.getValvePositionSensorStatus() ? "Operational" : "Not Operational") << std::endl;
    }

    static void adjustValvePosition(TurbineSpeedControlSystem& controlSystem) {
        try {
            float newPosition;
            std::cout << "Enter new Valve Position (0.0 to 1.0): ";
            std::cin >> newPosition;

            if (newPosition >= 0.0 && newPosition <= 1.0) {
                controlSystem.adjustValvePosition(newPosition);
                std::cout << "Valve Position adjusted successfully.\n";
            } else {
                std::cout << "Invalid Valve Position. Please enter a value between 0.0 and 1.0.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception caught during valve adjustment: " << e.what() << std::endl;
        }
    }

    static void displayCurrentRPM(const TurbineSpeedControlSystem& controlSystem) {
        std::cout << "Current RPM: " << controlSystem.getCurrentRPM() << std::endl;
    }

    static void displayValvePosition(const TurbineSpeedControlSystem& controlSystem) {
        std::cout << "Valve Position: " << controlSystem.getValvePosition() * 100 << "%\n";
    }

    static void displaySystemStatus(const TurbineSpeedControlSystem& controlSystem) {
        std::cout << "System Operational Status: " << (controlSystem.isSystemOperational() ? "Operational" : "Not Operational") << std::endl;
    }
};


// Main logic
    
 int main() {
       TurbineSpeedControlSystem controlSystem;

    for (int i = 0; i < 180; i++) {
        float rpmIncrease = std::min(50.0f, (TurbineSpeedControlSystem::targetRPM - controlSystem.rpmSensor.rpmReading) * 0.05f);
        float simulatedRPM = controlSystem.rpmSensor.rpmReading + rpmIncrease;
        controlSystem.rpmSensor.measureRPM(simulatedRPM);
        controlSystem.updateSensorStatus();

        if (controlSystem.isSystemOperational()) {
            controlSystem.compareRPM();

            std::cout << "System is operational. Time: " << i << "s, "
                      << "Current RPM: " << controlSystem.currentRPM << ", "
                      << "Valve Position: " << controlSystem.valvePosition * 100 << "%"
                      << std::endl;
        } else {
            std::cout << "Sensor failure detected. System is not operational." << std::endl;
        }
    }
    TurbineSpeedControlSystemTester::runTests();
    return 0;

}
