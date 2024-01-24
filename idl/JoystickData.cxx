// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file JoystickData.cpp
 * This source file contains the implementation of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include "JoystickData.h"

#include <fastcdr/Cdr.h>


#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>






JoystickData::JoystickData()
{
}

JoystickData::~JoystickData()
{
}

JoystickData::JoystickData(
        const JoystickData& x)
{
    m_buttonStates = x.m_buttonStates;
    m_axisStates = x.m_axisStates;
}

JoystickData::JoystickData(
        JoystickData&& x) noexcept
{
    m_buttonStates = std::move(x.m_buttonStates);
    m_axisStates = std::move(x.m_axisStates);
}

JoystickData& JoystickData::operator =(
        const JoystickData& x)
{

    m_buttonStates = x.m_buttonStates;
    m_axisStates = x.m_axisStates;
    return *this;
}

JoystickData& JoystickData::operator =(
        JoystickData&& x) noexcept
{

    m_buttonStates = std::move(x.m_buttonStates);
    m_axisStates = std::move(x.m_axisStates);
    return *this;
}

bool JoystickData::operator ==(
        const JoystickData& x) const
{
    return (m_buttonStates == x.m_buttonStates &&
           m_axisStates == x.m_axisStates);
}

bool JoystickData::operator !=(
        const JoystickData& x) const
{
    return !(*this == x);
}

/*!
 * @brief This function copies the value in member buttonStates
 * @param _buttonStates New value to be copied in member buttonStates
 */
void JoystickData::buttonStates(
        const std::vector<int32_t>& _buttonStates)
{
    m_buttonStates = _buttonStates;
}

/*!
 * @brief This function moves the value in member buttonStates
 * @param _buttonStates New value to be moved in member buttonStates
 */
void JoystickData::buttonStates(
        std::vector<int32_t>&& _buttonStates)
{
    m_buttonStates = std::move(_buttonStates);
}

/*!
 * @brief This function returns a constant reference to member buttonStates
 * @return Constant reference to member buttonStates
 */
const std::vector<int32_t>& JoystickData::buttonStates() const
{
    return m_buttonStates;
}

/*!
 * @brief This function returns a reference to member buttonStates
 * @return Reference to member buttonStates
 */
std::vector<int32_t>& JoystickData::buttonStates()
{
    return m_buttonStates;
}


/*!
 * @brief This function copies the value in member axisStates
 * @param _axisStates New value to be copied in member axisStates
 */
void JoystickData::axisStates(
        const std::vector<double>& _axisStates)
{
    m_axisStates = _axisStates;
}

/*!
 * @brief This function moves the value in member axisStates
 * @param _axisStates New value to be moved in member axisStates
 */
void JoystickData::axisStates(
        std::vector<double>&& _axisStates)
{
    m_axisStates = std::move(_axisStates);
}

/*!
 * @brief This function returns a constant reference to member axisStates
 * @return Constant reference to member axisStates
 */
const std::vector<double>& JoystickData::axisStates() const
{
    return m_axisStates;
}

/*!
 * @brief This function returns a reference to member axisStates
 * @return Reference to member axisStates
 */
std::vector<double>& JoystickData::axisStates()
{
    return m_axisStates;
}


// Include auxiliary functions like for serializing/deserializing.
#include "JoystickDataCdrAux.ipp"

