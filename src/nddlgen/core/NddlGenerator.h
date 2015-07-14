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

#ifndef CORE_NDDLGENERATOR_H_
#define CORE_NDDLGENERATOR_H_

#include <string>

#include "nddlgen/model/Arm.h"

namespace nddlgen { namespace core
{

	class NddlGenerator
	{

		private:

			nddlgen::model::Arm* _armModel;
			std::string _models;
			std::string _initialState;

		public:

			NddlGenerator(nddlgen::model::Arm* armModel);
			virtual ~NddlGenerator();

			bool generateModels();
			bool generateInitialState();

			bool writeModelsToFile();
			bool writeInitialStateToFile();

	};

}}

#endif