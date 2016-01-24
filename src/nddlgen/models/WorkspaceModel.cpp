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

#include <nddlgen/models/WorkspaceModel.h>

nddlgen::models::WorkspaceModel::WorkspaceModel()
{
	this->setClassName("Workspace");
}

nddlgen::models::WorkspaceModel::~WorkspaceModel()
{

}

void nddlgen::models::WorkspaceModel::addModelToWorkspace(nddlgen::models::NddlGeneratablePtr model)
{
	this->addSubObject(model);
}

nddlgen::models::NddlGeneratablePtr nddlgen::models::WorkspaceModel::getModelByName(std::string name)
{
	return this->getSubObjectByName(name);
}

nddlgen::types::NddlGeneratableList nddlgen::models::WorkspaceModel::getModels()
{
	return this->_subObjects;
}
