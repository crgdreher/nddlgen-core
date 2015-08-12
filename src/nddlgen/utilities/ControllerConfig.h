/**
 * Copyright 2015 Christian Dreher (dreher@charlydelta.org)
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

#ifndef NDDLGEN_UTILITIES_CONTROLLERCONFIG_H_
#define NDDLGEN_UTILITIES_CONTROLLERCONFIG_H_

#include <boost/filesystem.hpp>

#include <nddlgen/exceptions/ControllerConfigIsReadOnlyException.hpp>

namespace nddlgen { namespace utilities
{

	class ControllerConfig
	{

		private:

			std::string _adapter;
			std::string _inputSdfFile;
			std::string _inputIsdFile;
			std::string _outputFilesPath;
			bool _readOnly;

			void trySet();

			/**
			 * Normalizes existing and non-existing paths. From: http://stackoverflow.com/a/12797413/2938082
			 * Courtesy of jarzec (stackoverflow community member)
			 *
			 * @param path Path to be normalized
			 *
			 * @return Normalized path as string
			 */
			std::string normalizePath(const boost::filesystem::path &path);

		public:

			ControllerConfig();
			virtual ~ControllerConfig();

			void setAdapter(std::string adapter);
			void setInputSdfFile(std::string inputSdfFile);
			void setInputIsdFile(std::string inputIsdFile);
			void setOutputFilesPath(std::string outputFilesPath);
			void setReadOnly();

			std::string getAdapter();
			std::string getInputSdfFile();
			std::string getInputSdfFileExt();
			std::string getInputSdfFileName();
			std::string getInputSdfFilePath();
			std::string getInputIsdFile();
			std::string getInputIsdFileExt();
			std::string getInputIsdFileName();
			std::string getInputIsdFilePath();
			std::string getOutputFilesPath();
			std::string getOutputModelFile();
			std::string getOutputModelFileName();
			std::string getOutputInitialStateFile();
			std::string getOutputInitialStateFileName();

			bool isReadOnly();
	};

}}

#endif
