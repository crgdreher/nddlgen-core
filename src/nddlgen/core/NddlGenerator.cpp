/**
 * Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "nddlgen/core/NddlGenerator.h"

namespace nddlgen { namespace core
{

	NddlGenerator::NddlGenerator(nddlgen::model::Arm* armModel)
	{
		this->_armModel = armModel;
	}

	NddlGenerator::~NddlGenerator()
	{
		// TODO Auto-generated destructor stub
	}


	bool NddlGenerator::generateModels()
	{
		this->_models = this->_armModel->generateModelAsString();

		return true;
	}

	bool NddlGenerator::generateInitialState()
	{
		this->_initialState = this->_armModel->generateInitialStateAsString();

		return true;
	}


	bool NddlGenerator::writeModelsToFile()
	{
		// Write this->_models to file
		return true;
	}

	bool NddlGenerator::writeInitialStateToFile()
	{
		// Write this->_initialState to file
		return true;
	}

}}