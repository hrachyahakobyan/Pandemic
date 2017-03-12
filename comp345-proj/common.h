#pragma once

typedef unsigned int PlayerIndex;
typedef unsigned int RegionIndex;
typedef unsigned int RoleIndex;
typedef RegionIndex DiseaseType;

template<typename Archive>
static void registerTypes(Archive& ar)
{
	ar.template register_type<pan::Player<pan::Roles::Dispatcher>>();
	ar.template register_type<pan::Player<pan::Roles::FOperative>>();
	ar.template register_type<pan::Player<pan::Roles::Generalist>>();
	ar.template register_type<pan::Player<pan::Roles::Medic>>();
	ar.template register_type<pan::Player<pan::Roles::QSpecialist>>();
	ar.template register_type<pan::Player<pan::Roles::Researcher>>();
}