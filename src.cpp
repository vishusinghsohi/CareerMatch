g++ -std=c++17 -Iinclude (Get-ChildItem .\src\*.cpp).FullName -o CareerMatch.exe.\CareerMatch.exe#include "Skill.h"

Skill::Skill(const std::string& name, int proficiency)
    : name(name), proficiency(proficiency) {
}

std::string Skill::getName() const {
    return name;
}

int Skill::getProficiency() const {
    return proficiency;
}

void Skill::setProficiency(int proficiency) {
    this->proficiency = proficiency;
}

bool Skill::operator==(const Skill& other) const {
    return name == other.name;
}



























#include <iostream>
#include <memory>

#include "Candidate.h"
#include "Job.h"
#include "Skill.h"
#include "MatchResult.h"
#include "MatchingStrategy.h"
#include "SkillMatchingStrategy.h"

int main() {

    Candidate candidate(
        "Sarb",
        "sarb@example.com",
        1
    );

    candidate.addSkill(Skill("C++", 4));
    candidate.addSkill(Skill("Python", 4));
    candidate.addSkill(Skill("SQL", 3));
    candidate.addSkill(Skill("Git", 4));

    Job job(
        1,
        "Software Developer Intern",
        "TechNova",
        1
    );

    job.addRequiredSkill(Skill("C++"));
    job.addRequiredSkill(Skill("Git"));
    job.addRequiredSkill(Skill("SQL"));
    job.addRequiredSkill(Skill("Linux"));

    std::cout << "============================\n";
    std::cout << "CANDIDATE PROFILE\n";
    std::cout << "============================\n";

    candidate.displayProfile();

    std::cout << "\n============================\n";
    std::cout << "JOB INFORMATION\n";
    std::cout << "============================\n";

    job.displayJob();

    std::unique_ptr<MatchingStrategy> strategy =
        std::make_unique<SkillMatchingStrategy>();

    MatchResult result =
        strategy->calculateMatch(candidate, job);

    result.display();

    return 0;
}
























#include "User.h"

User::User(const std::string& name, const std::string& email)
    : name(name), email(email) {
}

std::string User::getName() const {
    return name;
}

std::string User::getEmail() const {
    return email;
}
























#include "Candidate.h"

#include <iostream>

Candidate::Candidate(
    const std::string& name,
    const std::string& email,
    int yearsOfExperience
)
    : User(name, email),
      yearsOfExperience(yearsOfExperience) {
}

void Candidate::addSkill(const Skill& skill) {
    skills.push_back(skill);
}

const std::vector<Skill>& Candidate::getSkills() const {
    return skills;
}

int Candidate::getYearsOfExperience() const {
    return yearsOfExperience;
}

void Candidate::displayProfile() const {

    std::cout << "Candidate: " << name << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Experience: "
              << yearsOfExperience
              << " years\n";

    std::cout << "Skills:\n";

    for (const Skill& skill : skills) {
        std::cout << "- " << skill.getName() << "\n";
    }
}

































#include "Job.h"

#include <iostream>

Job::Job(
    int id,
    const std::string& title,
    const std::string& company,
    int requiredExperience
)
    : id(id),
      title(title),
      company(company),
      requiredExperience(requiredExperience) {
}

void Job::addRequiredSkill(const Skill& skill) {
    requiredSkills.push_back(skill);
}

const std::vector<Skill>& Job::getRequiredSkills() const {
    return requiredSkills;
}

std::string Job::getTitle() const {
    return title;
}

std::string Job::getCompany() const {
    return company;
}

int Job::getRequiredExperience() const {
    return requiredExperience;
}

void Job::displayJob() const {

    std::cout << "\nJob: " << title << "\n";
    std::cout << "Company: " << company << "\n";

    std::cout << "Required Experience: "
              << requiredExperience
              << " years\n";

    std::cout << "Required Skills:\n";

    for (const Skill& skill : requiredSkills) {
        std::cout << "- " << skill.getName() << "\n";
    }
}





























#include "MatchResult.h"

#include <iostream>
#include <iomanip>

MatchResult::MatchResult(double score)
    : score(score) {
}

void MatchResult::setScore(double score) {
    this->score = score;
}

double MatchResult::getScore() const {
    return score;
}

void MatchResult::addMatchedSkill(const std::string& skill) {
    matchedSkills.push_back(skill);
}

void MatchResult::addMissingSkill(const std::string& skill) {
    missingSkills.push_back(skill);
}

const std::vector<std::string>& MatchResult::getMatchedSkills() const {
    return matchedSkills;
}

const std::vector<std::string>& MatchResult::getMissingSkills() const {
    return missingSkills;
}

void MatchResult::display() const {

    std::cout << "\n============================\n";
    std::cout << "MATCH RESULT\n";
    std::cout << "============================\n";

    std::cout << std::fixed << std::setprecision(1);

    std::cout << "Match Score: "
              << score
              << "%\n";

    std::cout << "\nMatched Skills:\n";

    for (const std::string& skill : matchedSkills) {
        std::cout << "- " << skill << "\n";
    }

    std::cout << "\nMissing Skills:\n";

    for (const std::string& skill : missingSkills) {
        std::cout << "- " << skill << "\n";
    }
}



























#include "SkillMatchingStrategy.h"

MatchResult SkillMatchingStrategy::calculateMatch(
    const Candidate& candidate,
    const Job& job
) const {

    MatchResult result;

    const std::vector<Skill>& candidateSkills =
        candidate.getSkills();

    const std::vector<Skill>& requiredSkills =
        job.getRequiredSkills();

    int matchedCount = 0;

    for (const Skill& requiredSkill : requiredSkills) {

        bool found = false;

        for (const Skill& candidateSkill : candidateSkills) {

            if (candidateSkill == requiredSkill) {

                found = true;
                matchedCount++;

                result.addMatchedSkill(
                    requiredSkill.getName()
                );

                break;
            }
        }

        if (!found) {

            result.addMissingSkill(
                requiredSkill.getName()
            );
        }
    }

    double score = 0.0;

    if (!requiredSkills.empty()) {

        score =
            static_cast<double>(matchedCount)
            / requiredSkills.size()
            * 100.0;
    }

    result.setScore(score);

    return result;
}