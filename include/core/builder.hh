#pragma once

/**
 * The Builder abstract class.
 *
 * The goal of the builder is to build an object of any type using the
 * `build` method.
 */
template <class ToBuildType>
class Builder
{
public:
    /**
     * The build abstract method.
     *
     * @return The built object.
     */
    virtual ToBuildType build() = 0;

    /**
     * Fill default values of the builder.
     *
     * Should be called in the constructor unless there is a specific reason
     * not to, for example if the default fields allocate memory that is not
     * needed.
     *
     * @return The builder object.
     */

    virtual Builder<ToBuildType> &base() = 0;
};
