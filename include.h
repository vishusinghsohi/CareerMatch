#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill {
private:
    std::string name;
    int proficiency;

public:
    Skill(const std::string& name, int proficiency = 1);

    std::string getName() const;
    int getProficiency() const;

    void setProficiency(int proficiency);

    bool operator==(const Skill& other) const;
};

#endif










#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string name;
    std::string email;

public:
    User(const std::string& name, const std::string& email);

    std::string getName() const;
    std::string getEmail() const;

    virtual void displayProfile() const = 0;

    virtual ~User() = default;
};

#endif


















#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "User.h"
#include "Skill.h"

#include <vector>

class Candidate : public User {
private:
    std::vector<Skill> skills;
    int yearsOfExperience;

public:
    Candidate(
        const std::string& name,
        const std::string& email,
        int yearsOfExperience
    );

    void addSkill(const Skill& skill);

    const std::vector<Skill>& getSkills() const;

    int getYearsOfExperience() const;

    void displayProfile() const override;
};

#endif



















#ifndef JOB_H
#define JOB_H

#include "Skill.h"

#include <string>
#include <vector>

class Job {
private:
    int id;
    std::string title;
    std::string company;

    std::vector<Skill> requiredSkills;

    int requiredExperience;

public:
    Job(
        int id,
        const std::string& title,
        const std::string& company,
        int requiredExperience
    );

    void addRequiredSkill(const Skill& skill);

    const std::vector<Skill>& getRequiredSkills() const;

    std::string getTitle() const;
    std::string getCompany() const;

    int getRequiredExperience() const;

    void displayJob() const;
};

#endif


























#ifndef MATCHRESULT_H
#define MATCHRESULT_H

#include <string>
#include <vector>

class MatchResult {
private:
    double score;

    std::vector<std::string> matchedSkills;
    std::vector<std::string> missingSkills;

public:
    MatchResult(double score = 0.0);

    void setScore(double score);

    double getScore() const;

    void addMatchedSkill(const std::string& skill);
    void addMissingSkill(const std::string& skill);

    const std::vector<std::string>& getMatchedSkills() const;

    const std::vector<std::string>& getMissingSkills() const;

    void display() const;
};

#endif




























#ifndef MATCHINGSTRATEGY_H
#define MATCHINGSTRATEGY_H

#include "Candidate.h"
#include "Job.h"
#include "MatchResult.h"

class MatchingStrategy {
public:

    virtual MatchResult calculateMatch(
        const Candidate& candidate,
        const Job& job
    ) const = 0;

    virtual ~MatchingStrategy() = default;
};

#endif




































#ifndef SKILLMATCHINGSTRATEGY_H
#define SKILLMATCHINGSTRATEGY_H

#include "MatchingStrategy.h"

class SkillMatchingStrategy : public MatchingStrategy {
public:

    MatchResult calculateMatch(
        const Candidate& candidate,
        const Job& job
    ) const override;
};

#endif







