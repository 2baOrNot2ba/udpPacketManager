#include "lofar_udp_backends.hpp"


// Declare the Stokes Vector Functions
#pragma omp declare simd
float stokesI(float Xr, float Xi, float Yr, float Yi) {
	return  (1.0 * (Xr * Xr) + 1.0 * (Xi * Xi) + 1.0 * (Yr * Yr) + 1.0 * (Yi * Yi));
}

#pragma omp declare simd
float stokesQ(float Xr, float Xi, float Yr, float Yi) {
	return  (1.0 * (Xr * Xr) + 1.0 * (Xi * Xi) - 1.0 * (Yr * Yr) - 1.0 * (Yi * Yi));
}

#pragma omp declare simd
float stokesU(float Xr, float Xi, float Yr, float Yi) {
	return  (2.0 * (Xr * Yr) - 3.0 * (Xi * Yi));
}

#pragma omp declare simd
float stokesV(float Xr, float Xi, float Yr, float Yi) {
	return 2.0 * ((Xr * Yi) + (-1.0 * Xi * Yr));
}


// Re-parsing processing modes
int lofar_udp_raw_udp_copy(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_udp_copy_cpp(meta);
		case 16:
			return lofar_udp_raw_udp_copy_cpp(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}


int lofar_udp_raw_udp_copy_nohdr(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, signed char, 1>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, signed short, 1>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}


int lofar_udp_raw_udp_copy_split_pols(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, signed char, 2>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, signed short, 2>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}


int lofar_udp_raw_udp_reorder(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, signed char, 10>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, signed short, 10>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}


int lofar_udp_raw_udp_reorder_split_pols(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, signed char, 11>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, signed short, 11>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}


int lofar_udp_raw_udp_reversed(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, signed char, 20>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, signed short, 20>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}


int lofar_udp_raw_udp_reversed_split_pols(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, signed char, 21>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, signed short, 21>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}





// Stokes Processing modes
// Stokes I, Q, U, V each have their own functions, and the option between no, 2x, 4x, 8x and 16x
// 	time decimation on the output.
int lofar_udp_raw_udp_stokesI(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 100>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 100>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesQ(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 110>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 110>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesU(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 120>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 120>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesV(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 130>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 130>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesI_sum2(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 101>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 101>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesQ_sum2(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 111>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 111>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesU_sum2(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 121>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 121>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesV_sum2(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 131>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 131>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}


int lofar_udp_raw_udp_stokesI_sum4(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 102>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 102>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesQ_sum4(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 112>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 112>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesU_sum4(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 122>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 122>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesV_sum4(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 132>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 132>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}


int lofar_udp_raw_udp_stokesI_sum8(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 103>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 103>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesQ_sum8(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 113>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 113>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesU_sum8(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 123>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 123>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesV_sum8(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 133>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 133>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesI_sum16(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 104>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 104>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesQ_sum16(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 114>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 114>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesU_sum16(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 124>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 124>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}

int lofar_udp_raw_udp_stokesV_sum16(lofar_udp_meta *meta) {
	switch(meta->inputBitMode) {
		case 4:
			fprintf(stderr, "4-bit mode is not yet supported, exiting.\n");
			return 1;
		case 8:
			return lofar_udp_raw_loop<signed char, float, 134>(meta);
		case 16:
			return lofar_udp_raw_loop<signed short, float, 134>(meta);

		default:
			fprintf(stderr, "Unexpected bitmode %d. Exiting.\n", meta->inputBitMode);
			return 1;
	}
}



// Header-included requires some extra logic tweaks
int lofar_udp_raw_udp_copy_cpp(lofar_udp_meta *meta) {
	// Setup working variables	
	VERBOSE(const int verbose = meta->VERBOSE);
	
	const int packetsPerIteration = meta->packetsPerIteration;
	const int replayDroppedPackets = meta->replayDroppedPackets;

	int packetLoss = 0;

	// For each port of data provided,
	omp_set_num_threads(OMP_THREADS);
	#pragma omp parallel for 
	for (int port = 0; port < meta->numPorts; port++) {
		VERBOSE(if (verbose) printf("Port: %d on thread %d\n", port, omp_get_thread_num()));

		long lastPortPacket, currentPortPacket, inputPacketOffset, outputPacketOffset, lastInputPacketOffset, iWork, iLoop;
		// Reset the dropped packets counter
		meta->portLastDroppedPackets[port] = 0;
		int currentPacketsDropped = 0, nextSequence;

		// Reset last packet, reference data on the current port
		lastPortPacket = meta->lastPacket;
		char  *inputPortData = meta->inputData[port];
		char  *outputData = (char*) meta->outputData[port];

		// Get the length of packets on the current port and reset the last packet variable encase
		// 	there is packet loss on the first packet
		const int portPacketLength = meta->portPacketLength[port];
		lastInputPacketOffset = (-2 + meta->replayDroppedPackets) * portPacketLength; 	// We request at least 2 packets are malloc'd before the array head pointer, so no SEGFAULTs here
														// -2 * PPL = 0s -1 * PPL = last processed packet -- used for calcuating offset in dropped case if 
														// 	we have packet loss on the boundary.
		VERBOSE(if (verbose) printf("LPP: %ld, PPL: %d, LIPO: %ld\n", lastPortPacket, portPacketLength, lastInputPacketOffset));
		// iWork -- input data offset calculations (account for dropped packets)
		// iLoop -- output data offsets
		// These are the same if there is no packet loss.
		// 
		// Reset iWork, inputPacketOffset, read in the first packet's number.
		iWork = 0, inputPacketOffset = 0;
		currentPortPacket = lofar_get_packet_number(&(inputPortData[inputPacketOffset]));
		VERBOSE(if (verbose) printf("Packet 0: %ld\n", currentPortPacket));
		
		for (iLoop = 0; iLoop < packetsPerIteration; iLoop++) {
			VERBOSE(if (verbose) printf("Loop %ld, Work %ld, packet %ld, target %ld\n", iLoop, iWork, currentPortPacket, lastPortPacket + 1));

			// Check for packet loss by ensuring we have sequential packet numbers
			if (currentPortPacket != (lastPortPacket + 1)) {
				// Check if a packet is out of order; if so, drop the packet
				// TODO: Better future option: check if the packet is in this block, copy and overwrite padded packed instead
				VERBOSE(if (verbose) printf("Packet %ld is not the expected packet, %ld.\n", currentPortPacket, lastPortPacket + 1));
				if (currentPortPacket < lastPortPacket) {
					
					VERBOSE(if(verbose) printf("Packet %ld on port %d is out of order (expected %ld); dropping.\n", currentPortPacket, port, lastPortPacket + 1));
					// Dropped packet -> index not processed -> effectively an 'added' packet, decrement the dropped packet count
					// 	so that we don't include an extra packet in shift operations
					currentPacketsDropped -= 1;

					iWork++;
					if (iWork != packetsPerIteration) {
						inputPacketOffset = iWork * portPacketLength;
						currentPortPacket = lofar_get_packet_number(&(inputPortData[inputPacketOffset]));
					}
					continue;

				}

				// Packet dropped:
				//  Trip the return int
				//	Increment the port counter for this operation
				//	Increment the last packet offset so it can be used again next time, including the new offset
				packetLoss = -1;
				currentPacketsDropped += 1;
				lastPortPacket += 1;

				if (replayDroppedPackets) {
					// If we are replaying the last packet, change the array index to the last good packet index
					inputPacketOffset = lastInputPacketOffset;
				} else {
					// Array should be 0 padded at the start; copy data from there.
					inputPacketOffset = -2 * portPacketLength;
					// Move the last header into place
					memcpy(&(inputPortData[inputPacketOffset + 8]), &(inputPortData[lastInputPacketOffset + 8]), 8);
				}

				// Increment the 'sequence' component of the header so that the packet number appears right in future packet reads
				nextSequence = lofar_get_next_packet_sequence(&(inputPortData[lastInputPacketOffset]));
				memcpy(&(inputPortData[inputPacketOffset + 12]), &nextSequence, 4);
				// The last bit of the 'source' short isn't used; leave a signature that this packet was modified
				// Mask off the rest of the byte before adding encase we've used this packet before
				inputPortData[inputPacketOffset + 2] = (inputPortData[inputPacketOffset + 2] & 127) + 128;

				VERBOSE(if (verbose) printf("Packet %ld on port %d is missing; padding.\n", lastPortPacket + 1, port));

			} else {
				VERBOSE(if (verbose) printf("Packet %ld is the expected packet.\n", currentPortPacket));

				lastPortPacket = currentPortPacket;
				// Speedup: add 4 to the sequence, check if accurate. Doesn't work at rollover.
				if  (((char_unsigned_int*) &(inputPortData[inputPacketOffset + 12]))->ui  == (((char_unsigned_int*) &(inputPortData[lastInputPacketOffset -4])))->ui + 16)  {
					currentPortPacket += 1;
				} else currentPortPacket = lofar_get_packet_number(&(inputPortData[inputPacketOffset]));
				
				// We have a sequential packet, therefore:
				//		Update the last legitimate packet number and array offset index
				//		Increment iWork (input data packet index) and determine the new input offset
				//		Get the next packet number for the next loop
				lastInputPacketOffset = inputPacketOffset;

				iWork++;
				inputPacketOffset = iWork * portPacketLength;

			}

			// Move the packet (or substitute) to the output data
			outputPacketOffset = iLoop * portPacketLength;
			//VERBOSE(if (verbose) printf("Copying %d data from %ld to %ld\n", portPacketLength, lastInputPacketOffset, outputPacketOffset));
			memcpy(&(outputData[outputPacketOffset]), &(inputPortData[lastInputPacketOffset]), portPacketLength);
			

		}
		// Update the overall dropped packet count for this port

		meta->portLastDroppedPackets[port] = currentPacketsDropped;
		meta->portTotalDroppedPackets[port] += currentPacketsDropped;
		VERBOSE(if (verbose) printf("Current dropped packet count on port %d: %d\n", port, meta->portLastDroppedPackets[port]));
	}

	for (int port = 0; port < meta->numPorts; port++) {
		if (meta->portLastDroppedPackets[port] < (-0.001 * (float) packetsPerIteration)) {
			fprintf(stderr, "A large number of packets were out of order on port %d; this normally indicates a data integrity issue, exiting...", port);
			return 1;
		}
	}

	for (int port =0; port < meta->numPorts; port++) {
		if (meta->portLastDroppedPackets[port] < 0 && meta->replayDroppedPackets) {
			// TODO: pad the end of the arrays if the data doesn't fill it.
			// Or just re-loop with fresh data and report less data back?
			// Maybe rearchitect a bit, overread the amount of data needed, only return what's needed.
		}
	}

	// Update the last packet variable
	meta->lastPacket += packetsPerIteration;
	VERBOSE(if (verbose) printf("Exiting operation, last packet was %ld\n", meta->lastPacket));

	// Update the input/output states
	meta->inputDataReady = 0;
	meta->outputDataReady = 1;

	return packetLoss;
}