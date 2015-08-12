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

#include <nddlgen/Controller.h>

namespace nddlgen
{

	Controller::Controller(nddlgen::utilities::ControllerConfig* config)
	{
		// Mark config object as read only, set local config member
		config->setReadOnly();
		this->_config = config;

		// Save standard cerr buffer to be able to restore it
		this->_cerrStdRdBuf = std::cerr.rdbuf();

		// Initialize model workflow indicators
		this->_isSdfChecked = false;
		this->_isSdfParsed = false;
		this->_isNddlModelGenerated = false;

		// Initialize initial state workflow indicators
		this->_isIsdChecked = false;
		this->_isIsdParsed = false;
		this->_isNddlInitialStateGenerated = false;

		// Instantiate arm model
		this->_armModel = new nddlgen::models::Arm();
	}

	Controller::~Controller()
	{
		boost::checked_delete(this->_armModel);

		// Check if SDF was parsed before calling member functions on SDF root
		if (this->_isSdfParsed)
		{
			this->_sdfRoot->ClearElements();
		}
	}


	void Controller::checkSdfInput()
	{
		sdf::SDFPtr sdf(new sdf::SDF);

		// Check if SDF has already been checked
		if (this->_isSdfChecked)
		{
			throw nddlgen::exceptions::SdfAlreadyCheckedException();
		}

		// Check if input SDF file has been set
		if (this->_config->getInputSdfFile() == "")
		{
			throw nddlgen::exceptions::InputSdfFileNotSetException();
		}

		// Check if input SDF file is an .sdf file
		if (this->_config->getInputSdfFileExt() != ".sdf")
		{
			throw nddlgen::exceptions::FileMustBeSdfException();
		}

		// Check if SDF file exists
		if (!boost::filesystem::exists(this->_config->getInputSdfFile()))
		{
			throw nddlgen::exceptions::FileDoesNotExistException(this->_config->getInputSdfFile());
		}

		// Disable standard cerr output, since the output of the SDF library can't be suppressed otherwise
		this->disableCerr();

		// Init .sdf based on installed sdf_format.xml file
		if (!sdf::init(sdf))
		{
			// Re-enable standard cerr
			this->enableCerr();
			throw nddlgen::exceptions::InitializingSdfException(this->getBufferedCerrOutput());
		}

		// Try to read the file and generate SDF
		if (!sdf::readFile(this->_config->getInputSdfFile(), sdf))
		{
			// Re-enable cerr
			this->enableCerr();
			throw nddlgen::exceptions::ReadingSdfFileException(this->getBufferedCerrOutput());
		}

		// Save root to member
		this->_sdfRoot = sdf->root;

		// Re-enable cerr
		this->enableCerr();

		// Check workflow control variable
		this->_isSdfChecked = true;
	}

	void Controller::parseSdf()
	{
		// Check if file has already been parsed
		if (this->_isSdfParsed)
		{
			throw nddlgen::exceptions::SdfAlreadyParsedException();
		}

		// Check if file is parsable
		this->isSdfParsable();

		// Initialize the parser with the already initialized Arm model
		nddlgen::core::SdfParser* sdfParser = new nddlgen::core::SdfParser(this->_armModel);

		// Parse the SDF into the defined data structure and check if it was successful
		if (!sdfParser->parseDataStructure(this->_sdfRoot))
		{
			throw nddlgen::exceptions::ParseDataStructureException();
		}

		// Delete SDF parser
		boost::checked_delete(sdfParser);

		// Check workflow control variable
		this->_isSdfParsed = true;
	}

	void Controller::generateNddlModel()
	{
		this->generateNddlModel(false);
	}

	void Controller::generateNddlModel(bool forceOverwrite)
	{
		// Check if NDDL has already been generated
		if (this->_isNddlModelGenerated)
		{
			throw nddlgen::exceptions::NddlModelAlreadyGeneratedException();
		}

		// Check if files are generatable
		this->isNddlModelGeneratable();

		std::string nddlOutputModelFile = this->_config->getOutputModelFile();

		// Check if file already exists
		if (!forceOverwrite && boost::filesystem::exists(nddlOutputModelFile))
		{
			throw nddlgen::exceptions::FileAlreadyExists(nddlOutputModelFile);
		}

		// Initialize the NDDL generator with the already initialized and populated Arm model
		nddlgen::core::NddlGenerator* nddlgen = new nddlgen::core::NddlGenerator(this->_armModel, this->_config);

		// Try to generate domain models, write it to a file and check if it was successful
		if (!nddlgen->generateModels(nddlOutputModelFile))
		{
			throw nddlgen::exceptions::GeneratingModelsException();
		}

		// Delete NDDL generator
		boost::checked_delete(nddlgen);

		// Check workflow control variable
		this->_isNddlModelGenerated = true;
	}


	void Controller::checkIsdInput()
	{
		sdf::SDFPtr sdf(new sdf::SDF);

		// Check if ISD has already been checked
		if (this->_isIsdChecked)
		{
			throw nddlgen::exceptions::IsdAlreadyCheckedException();
		}

		// Check if input ISD file has been set
		if (this->_config->getInputIsdFile() == "")
		{
			throw nddlgen::exceptions::InputIsdFileNotSetException();
		}

		// Check if input ISD file is an .isd file
		if (this->_config->getInputIsdFileExt() != ".isd")
		{
			throw nddlgen::exceptions::FileMustBeIsdException();
		}

		// Check if file exists
		if (!boost::filesystem::exists(this->_config->getInputIsdFile()))
		{
			throw nddlgen::exceptions::FileDoesNotExistException(this->_config->getInputIsdFile());
		}

		// todo: get contents from isd file with tinyxml

		// Check workflow control variable
		this->_isIsdChecked = true;
	}

	void Controller::parseIsd()
	{
		// Check if file has already been parsed
		if (this->_isIsdParsed)
		{
			throw nddlgen::exceptions::IsdAlreadyParsedException();
		}

		// Check if file is parsable
		this->isIsdParsable();

		// todo: parse xml from tinyxml

		// Check workflow control variable
		this->_isIsdParsed = true;
	}

	void Controller::generateNddlInitialState()
	{
		this->generateNddlInitialState(false);
	}

	void Controller::generateNddlInitialState(bool forceOverwrite)
	{
		// Check if NDDL has already been generated
		if (this->_isNddlInitialStateGenerated)
		{
			throw nddlgen::exceptions::NddlInitialStateAlreadyGeneratedException();
		}

		// Check if files are generatable
		this->isNddlInitialStateGeneratable();

		std::string nddlOutputInitialStateFile = this->_config->getOutputInitialStateFile();

		// Check if file already exists
		if (!forceOverwrite && boost::filesystem::exists(nddlOutputInitialStateFile))
		{
			throw nddlgen::exceptions::FileAlreadyExists(nddlOutputInitialStateFile);
		}

		// Initialize the NDDL generator with the already initialized and populated Arm model
		nddlgen::core::NddlGenerator* nddlgen = new nddlgen::core::NddlGenerator(this->_armModel, this->_config);

		// Try to generate domain initial state and check if it was successful
		if (!nddlgen->generateInitialState(nddlOutputInitialStateFile))
		{
			throw nddlgen::exceptions::GeneratingInitialStateException();
		}

		// Delete NDDL generator
		boost::checked_delete(nddlgen);

		// Check workflow control variable
		this->_isNddlInitialStateGenerated = true;
	}


	void Controller::isSdfParsable()
	{
		// Check if SDF file was checked
		if (!this->_isSdfChecked)
		{
			throw nddlgen::exceptions::CheckSdfFirstException();
		}
	}

	void Controller::isNddlModelGeneratable()
	{
		// Check if SDF is parsable
		this->isSdfParsable();

		// Check if SDF was parsed
		if (!this->_isSdfParsed)
		{
			throw nddlgen::exceptions::ParseSdfFirstException();
		}
	}


	void Controller::isIsdParsable()
	{
		// Check if ISD file was checked
		if (!this->_isIsdChecked)
		{
			throw nddlgen::exceptions::CheckIsdFirstException();
		}
	}

	void Controller::isNddlInitialStateGeneratable()
	{
		// Check if ISD is parsable
		this->isIsdParsable();

		// Check if ISD was parsed
		if (!this->_isIsdParsed)
		{
			throw nddlgen::exceptions::ParseIsdFirstException();
		}
	}


	void Controller::disableCerr()
	{
		std::cerr.rdbuf(this->_cerrOvRdBuf.rdbuf());
	}

	void Controller::enableCerr()
	{
		std::cerr.rdbuf(this->_cerrStdRdBuf);
	}

	std::string Controller::getBufferedCerrOutput()
	{
		return this->_cerrOvRdBuf.str();
	}

}
