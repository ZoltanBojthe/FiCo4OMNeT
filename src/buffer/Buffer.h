#ifndef __FICO4OMNET_BUFFER_H_
#define __FICO4OMNET_BUFFER_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

namespace FiCo4OMNeT {

/**
 * @brief Represents the content of a physical buffer on a CAN_Node 
 *
 * Nodes will make it possible to read from a buffer after receiving a related Data-Frame.
 * It is possible to write the data you wish to send into a buffer.
 *
 * @sa CAN_Node
 *
 */

class Buffer: public cSimpleModule {
public:
    /**
     * @brief This method registers the gate for the reception of the messages.
     */
    virtual void registerDestinationGate();

    /**
     *
     * @return A pointer to the DataFrame with the corresponding ID. Returns
     * null if there is no DataFrame in the buffer.
     *
     */
    cMessage* getFrame(int id);

    /**
     * @brief Puts the frame into the collection and informs the connected gates about the reception.
     *
     * @param frame The DataFrame to put in the buffer.
     *
     */
    virtual void putFrame(cMessage* frame);

    /**
     * @brief Deletes the frame with the corresponding id from the frames collection.
     */
    virtual void deleteFrame(int id);

    /**
     * @brief Forwards the frame with the corresponding id to all destination gates.
     */
    virtual void deliverFrame(int id);

    /**
     * @brief Forwards the first received frame to all destination gates.
     */
    virtual void deliverNextFrame();

protected:
    /**
     * Stores the Gates to that the messages are delivered
     */
    std::list<cGate*> destinationGates;

    /**
     * @brief Queue for the EtherFrames in the Buffer.
     */
    std::list<cMessage*> frames;

    /**
     * Signal that is emitted every time a frame was sent.
     */
    simsignal_t txPkSignal;
    /**
     * Signal that is emitted every time a frame was received.
     */
    simsignal_t rxPkSignal;

    /**
     * @brief Initialization of the module.
     */
    virtual void initialize();

    virtual void finish();

    /**
     * @brief Is called when a new Frame is received in the buffer.
     *
     * When a frame is received on the in-Gate it is processed. If the destination
     * address is unspecified it is set according to the ct marker of the buffer.
     * Afterwards it is enqueued using the buffer specific enqueue(EtherFrame *newFrame)
     * method. In the end all registered receive callbacks are executed.
     *
     * @param msg The incoming message
     */
    virtual void handleMessage(cMessage *msg);

    /**
     * @brief Emits a statistics signal that a frame was sent from the buffer
     *
     * @param frame the frame that was sent
     */
    void recordPacketSent(cMessage *frame);

    /**
     * @brief Emits a statistics signal that a frame was received in the buffer
     *
     * @param frame the frame that was received
     */
    void recordPacketReceived(cMessage *frame);

    /**
     * @brief The message is delivered to the destination.
     */
    virtual void sendToDestinationGates(cMessage *msg);

private:

    /**
     * Initializes the statistics for the module
     */
    void initializeStatistics();



};

}
#endif
