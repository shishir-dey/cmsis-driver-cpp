#include <gmock/gmock.h>
#include "GPIO.hpp"

namespace cmsis
{
    class MockGPIO : public GPIO
    {
    public:
        MOCK_METHOD(int32_t, setup, (Pin pin, typename GPIO::SignalEventCallback callback), (override));
        MOCK_METHOD(int32_t, setDirection, (Pin pin, Direction direction), (override));
        MOCK_METHOD(int32_t, setOutputMode, (Pin pin, OutputMode mode), (override));
        MOCK_METHOD(int32_t, setPullResistor, (Pin pin, PullResistor resistor), (override));
        MOCK_METHOD(int32_t, setEventTrigger, (Pin pin, EventTrigger trigger), (override));
        MOCK_METHOD(void, setOutput, (Pin pin, uint32_t value), (override));
        MOCK_METHOD(uint32_t, getInput, (Pin pin), (const, override));
    };

    class GPIOTest : public ::testing::Test
    {
    protected:
        MockGPIO mock_gpio; // Mock instance for testing
    };

    // Test: Verify setup is called with the correct parameters
    TEST_F(GPIOTest, TestSetupCallback)
    {
        Pin test_pin = 10;
        auto callback = [](Pin pin, EventType event)
        {
            // Handle event
        };

        EXPECT_CALL(mock_gpio, setup(test_pin, ::testing::_))
            .Times(1)
            .WillOnce(::testing::Return(0)); // Simulate success

        int32_t result = mock_gpio.setup(test_pin, callback);
        EXPECT_EQ(result, 0);
    }

    // Test: Verify setDirection is called correctly for Input
    TEST_F(GPIOTest, TestSetDirectionInput)
    {
        Pin test_pin = 20;

        EXPECT_CALL(mock_gpio, setDirection(test_pin, Direction::Input))
            .Times(1)
            .WillOnce(::testing::Return(0));

        int32_t result = mock_gpio.setDirection(test_pin, Direction::Input);
        EXPECT_EQ(result, 0);
    }

    // Test: Verify setDirection is called correctly for Output
    TEST_F(GPIOTest, TestSetDirectionOutput)
    {
        Pin test_pin = 30;

        EXPECT_CALL(mock_gpio, setDirection(test_pin, Direction::Output))
            .Times(1)
            .WillOnce(::testing::Return(0));

        int32_t result = mock_gpio.setDirection(test_pin, Direction::Output);
        EXPECT_EQ(result, 0);
    }

    // Test: Verify setOutputMode is called with valid arguments
    TEST_F(GPIOTest, TestSetOutputMode)
    {
        Pin test_pin = 15;

        EXPECT_CALL(mock_gpio, setOutputMode(test_pin, OutputMode::PushPull))
            .Times(1)
            .WillOnce(::testing::Return(0));

        int32_t result = mock_gpio.setOutputMode(test_pin, OutputMode::PushPull);
        EXPECT_EQ(result, 0);
    }

    // Test: Verify setPullResistor is called with PullUp
    TEST_F(GPIOTest, TestSetPullResistorPullUp)
    {
        Pin test_pin = 25;

        EXPECT_CALL(mock_gpio, setPullResistor(test_pin, PullResistor::PullUp))
            .Times(1)
            .WillOnce(::testing::Return(0));

        int32_t result = mock_gpio.setPullResistor(test_pin, PullResistor::PullUp);
        EXPECT_EQ(result, 0);
    }

    // Test: Verify setPullResistor is called with None
    TEST_F(GPIOTest, TestSetPullResistorNone)
    {
        Pin test_pin = 25;

        EXPECT_CALL(mock_gpio, setPullResistor(test_pin, PullResistor::None))
            .Times(1)
            .WillOnce(::testing::Return(0));

        int32_t result = mock_gpio.setPullResistor(test_pin, PullResistor::None);
        EXPECT_EQ(result, 0);
    }

    // Test: Verify setEventTrigger is called correctly
    TEST_F(GPIOTest, TestSetEventTrigger)
    {
        Pin test_pin = 50;

        EXPECT_CALL(mock_gpio, setEventTrigger(test_pin, EventTrigger::RisingEdge))
            .Times(1)
            .WillOnce(::testing::Return(0));

        int32_t result = mock_gpio.setEventTrigger(test_pin, EventTrigger::RisingEdge);
        EXPECT_EQ(result, 0);
    }

    // Test: Verify setOutput is called correctly
    TEST_F(GPIOTest, TestSetOutput)
    {
        Pin test_pin = 60;
        uint32_t value = 1;

        EXPECT_CALL(mock_gpio, setOutput(test_pin, value))
            .Times(1);

        mock_gpio.setOutput(test_pin, value);
    }

    // Test: Verify getInput returns expected value
    TEST_F(GPIOTest, TestGetInput)
    {
        Pin test_pin = 70;

        EXPECT_CALL(mock_gpio, getInput(test_pin))
            .Times(1)
            .WillOnce(::testing::Return(1)); // Simulate a high input value

        uint32_t result = mock_gpio.getInput(test_pin);
        EXPECT_EQ(result, 1);
    }

    // Test: Verify multiple calls to setup with different pins
    TEST_F(GPIOTest, TestMultipleSetupCalls)
    {
        Pin pin1 = 80, pin2 = 90;

        EXPECT_CALL(mock_gpio, setup(pin1, ::testing::_))
            .Times(1)
            .WillOnce(::testing::Return(0));

        EXPECT_CALL(mock_gpio, setup(pin2, ::testing::_))
            .Times(1)
            .WillOnce(::testing::Return(-1)); // Simulate failure

        auto callback = [](Pin pin, EventType event) {};

        EXPECT_EQ(mock_gpio.setup(pin1, callback), 0);
        EXPECT_EQ(mock_gpio.setup(pin2, callback), -1);
    }

    // Test: Verify no unexpected calls occur
    TEST_F(GPIOTest, TestNoUnexpectedCalls)
    {
        EXPECT_CALL(mock_gpio, setup(::testing::_, ::testing::_)).Times(0);
        EXPECT_CALL(mock_gpio, setDirection(::testing::_, ::testing::_)).Times(0);
        EXPECT_CALL(mock_gpio, setOutput(::testing::_, ::testing::_)).Times(0);

        // No calls made here
    }

    // Test: Verify event callback is invoked correctly
    TEST_F(GPIOTest, TestEventCallback)
    {
        Pin test_pin = 42;
        bool callback_invoked = false;

        auto callback = [&](Pin pin, EventType event)
        {
            callback_invoked = true;
            EXPECT_EQ(pin, test_pin);
            EXPECT_EQ(event, EventType::RisingEdge);
        };

        EXPECT_CALL(mock_gpio, setup(test_pin, ::testing::_))
            .Times(1)
            .WillOnce(::testing::Invoke([&](Pin pin, GPIO::SignalEventCallback cb)
                                        {
            cb(pin, EventType::RisingEdge);
            return 0; }));

        mock_gpio.setup(test_pin, callback);
        EXPECT_TRUE(callback_invoked);
    }
}
