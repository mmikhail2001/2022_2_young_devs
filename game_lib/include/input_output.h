#pragma once

#include "game_field.h"
#include <cstdint>
#include <string>
#include <vector>

class IInput
{
  public:
    virtual uint16_t InputIndex() = 0;
    virtual void Undo() = 0;
};

class IOutput
{
  public:
    virtual void Output(IGameField *field) const = 0;
    virtual void OutputMsg(std::string const &message) const = 0;
};

class InputConsole : public IInput
{
  private:
    std::vector<uint16_t> _seqIndices;

  public:
    virtual uint16_t InputIndex() override;
    virtual void Undo() override;
};

class InputEvent : public IInput
{
  private:
    std::vector<uint16_t> _seqIndices;

  public:
    virtual uint16_t InputIndex() override;
    virtual void Undo() override;
};

class OutputConsole : public IOutput
{
  public:
    virtual void Output(IGameField *field) const override;
    virtual void OutputMsg(std::string const &message) const override;
};
